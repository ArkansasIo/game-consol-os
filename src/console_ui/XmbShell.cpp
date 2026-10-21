#include "console_ui/UI.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace console::ui {

XmbShell::XmbShell(UiTheme theme) : theme_(theme) {}

void XmbShell::addItem(UiItem item) {
    items_.push_back(std::move(item));
    normalizeSelection();
}

void XmbShell::normalizeSelection() {
    if (items_.empty()) {
        selectedIndex_ = 0;
        return;
    }
    selectedIndex_ = std::min(selectedIndex_, items_.size() - 1);
    if (!items_[selectedIndex_].enabled) {
        for (std::size_t i = 0; i < items_.size(); ++i) {
            if (items_[i].enabled) {
                selectedIndex_ = i;
                break;
            }
        }
    }
    for (auto& item : items_) item.state = FocusState::Normal;
    items_[selectedIndex_].state = FocusState::Focused;
}

void XmbShell::move(Direction direction) {
    if (items_.empty()) return;
    if (direction != Direction::Left && direction != Direction::Right &&
        direction != Direction::Up && direction != Direction::Down) return;

    const int delta = (direction == Direction::Left || direction == Direction::Up) ? -1 : 1;
    const auto count = static_cast<int>(items_.size());
    auto next = static_cast<int>(selectedIndex_) + delta;
    next = (next % count + count) % count;

    for (int attempts = 0; attempts < count; ++attempts) {
        if (items_[static_cast<std::size_t>(next)].enabled) {
            selectedIndex_ = static_cast<std::size_t>(next);
            normalizeSelection();
            return;
        }
        next = (next + delta + count) % count;
    }
}

void XmbShell::activate() {
    if (items_.empty() || !items_[selectedIndex_].enabled) return;
    items_[selectedIndex_].state = FocusState::Pressed;
    const auto item = items_[selectedIndex_];
    if (onActivate_) onActivate_(item);
    setScreen(item.destination);
}

void XmbShell::back() {
    setScreen(Screen::Home);
}

void XmbShell::setScreen(Screen screen) {
    if (screen_ == screen) return;
    screen_ = screen;
    transition_ = Animation{
        .duration = 0.22F,
        .elapsed = 0.0F,
        .easing = Easing::EaseOutCubic,
        .update = [this](float t) {
            for (auto& item : items_) item.transform.opacity = t;
        }
    };
}

void XmbShell::setOnActivate(std::function<void(const UiItem&)> callback) {
    onActivate_ = std::move(callback);
}

void XmbShell::tick(float deltaSeconds) {
    if (transition_) {
        transition_->tick(deltaSeconds);
        if (transition_->finished()) transition_.reset();
    }
}

void XmbShell::render(IRenderer& renderer, float viewportWidth, float viewportHeight) const {
    renderer.beginFrame(theme_.background);

    constexpr float tileWidth = 180.0F;
    constexpr float tileHeight = 118.0F;
    constexpr float gap = 24.0F;
    const float centerX = viewportWidth * 0.5F;
    const float centerY = viewportHeight * 0.50F;

    for (std::size_t i = 0; i < items_.size(); ++i) {
        const auto& item = items_[i];
        const float distance = static_cast<float>(static_cast<int>(i) - static_cast<int>(selectedIndex_));
        const float clamped = std::clamp(distance, -3.0F, 3.0F);
        const bool focused = i == selectedIndex_;
        const float scale = focused ? 1.10F : std::max(0.78F, 1.0F - std::abs(clamped) * 0.055F);
        const float x = centerX + clamped * (tileWidth + gap) - (tileWidth * scale) * 0.5F;
        const float y = centerY - (tileHeight * scale) * 0.5F;
        const Color panel = focused ? theme_.accent : theme_.panel;
        const float alpha = focused ? 0.92F : 0.78F;

        renderer.drawPanel(Rect{x, y, tileWidth * scale, tileHeight * scale},
                           Color{panel.r, panel.g, panel.b, alpha}, theme_.cornerRadius);
        renderer.drawIcon(item.icon, Vec2{x + 22.0F, y + 25.0F}, 40.0F * scale,
                          focused ? theme_.text : theme_.mutedText);
        renderer.drawText(item.title, Vec2{x + 22.0F, y + 72.0F}, 22.0F * scale,
                          theme_.text);
    }

    if (!items_.empty()) {
        const auto& selected = items_[selectedIndex_];
        renderer.drawText(selected.subtitle, Vec2{centerX - 260.0F, viewportHeight - 96.0F},
                          18.0F, theme_.mutedText);
        renderer.drawLine(Vec2{centerX - 260.0F, viewportHeight - 64.0F},
                          Vec2{centerX + 260.0F, viewportHeight - 64.0F}, 2.0F,
                          theme_.focusedGlow);
    }

    renderer.endFrame();
}

} // namespace console::ui

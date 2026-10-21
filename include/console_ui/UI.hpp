#pragma once

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace console::ui {

enum class Direction { Left, Right, Up, Down, Confirm, Back };
enum class Screen { Home, Games, Media, Library, Settings, Profile, Store };
enum class FocusState { Normal, Focused, Pressed, Disabled };

enum class Easing { Linear, EaseOutCubic, EaseInOutCubic };

struct Vec2 {
    float x{};
    float y{};
};

struct Color {
    float r{};
    float g{};
    float b{};
    float a{1.0F};
};

struct Rect {
    float x{};
    float y{};
    float width{};
    float height{};
};

struct UiTransform {
    Vec2 position{};
    Vec2 scale{1.0F, 1.0F};
    float rotation{};
    float opacity{1.0F};
};

struct UiTheme {
    Color background{0.015F, 0.025F, 0.045F, 1.0F};
    Color panel{0.035F, 0.060F, 0.100F, 0.94F};
    Color accent{0.20F, 0.70F, 1.0F, 1.0F};
    Color text{0.92F, 0.97F, 1.0F, 1.0F};
    Color mutedText{0.52F, 0.65F, 0.76F, 1.0F};
    Color focusedGlow{0.25F, 0.80F, 1.0F, 0.30F};
    float cornerRadius{14.0F};
};

struct UiItem {
    std::string id;
    std::string title;
    std::string subtitle;
    std::string icon;
    Screen destination{Screen::Home};
    bool enabled{true};
    FocusState state{FocusState::Normal};
    UiTransform transform{};
};

struct Animation {
    float duration{};
    float elapsed{};
    Easing easing{Easing::EaseOutCubic};
    std::function<void(float)> update;
    bool finished() const noexcept { return elapsed >= duration; }
    void tick(float deltaSeconds);
};

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void beginFrame(const Color& clearColor) = 0;
    virtual void drawPanel(const Rect& rect, const Color& color, float radius) = 0;
    virtual void drawText(std::string_view text, Vec2 position, float size, const Color& color) = 0;
    virtual void drawIcon(std::string_view icon, Vec2 position, float size, const Color& color) = 0;
    virtual void drawLine(Vec2 from, Vec2 to, float thickness, const Color& color) = 0;
    virtual void endFrame() = 0;
};

class InputRouter {
public:
    using Callback = std::function<void(Direction)>;
    void setCallback(Callback callback);
    void submit(Direction direction);
private:
    Callback callback_;
};

class XmbShell {
public:
    explicit XmbShell(UiTheme theme = {});

    void addItem(UiItem item);
    void move(Direction direction);
    void activate();
    void back();
    void tick(float deltaSeconds);
    void render(IRenderer& renderer, float viewportWidth, float viewportHeight) const;

    [[nodiscard]] Screen screen() const noexcept { return screen_; }
    [[nodiscard]] std::size_t selectedIndex() const noexcept { return selectedIndex_; }
    [[nodiscard]] const std::vector<UiItem>& items() const noexcept { return items_; }
    [[nodiscard]] const UiTheme& theme() const noexcept { return theme_; }

    void setScreen(Screen screen);
    void setOnActivate(std::function<void(const UiItem&)> callback);

private:
    std::vector<UiItem> items_;
    UiTheme theme_;
    Screen screen_{Screen::Home};
    std::size_t selectedIndex_{};
    std::optional<Animation> transition_;
    std::function<void(const UiItem&)> onActivate_;

    void normalizeSelection();
};

class Application {
public:
    Application();
    void tick(float deltaSeconds);
    void render(IRenderer& renderer, float width, float height) const;
    [[nodiscard]] XmbShell& shell() noexcept { return shell_; }
    [[nodiscard]] const XmbShell& shell() const noexcept { return shell_; }
private:
    XmbShell shell_;
};

} // namespace console::ui

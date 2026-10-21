#include "console_ui/UI.hpp"

#include <iostream>

namespace {
class ConsoleRenderer final : public console::ui::IRenderer {
public:
    void beginFrame(const console::ui::Color&) override {}
    void drawPanel(const console::ui::Rect&, const console::ui::Color&, float) override {}
    void drawText(std::string_view text, console::ui::Vec2, float, const console::ui::Color&) override {
        std::cout << "[TEXT] " << text << '\n';
    }
    void drawIcon(std::string_view icon, console::ui::Vec2, float, const console::ui::Color&) override {
        std::cout << "[ICON] " << icon << '\n';
    }
    void drawLine(console::ui::Vec2, console::ui::Vec2, float, const console::ui::Color&) override {}
    void endFrame() override {}
};
}

int main() {
    console::ui::Application app;
    ConsoleRenderer renderer;
    app.render(renderer, 1920.0F, 1080.0F);
    return 0;
}

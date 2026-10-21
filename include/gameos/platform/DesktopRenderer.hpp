#pragma once

#include "console_ui/UI.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace gameos::platform {

class DesktopRenderer final : public console::ui::IRenderer {
public:
    DesktopRenderer(SDL_Window* window, SDL_Renderer* renderer);
    ~DesktopRenderer() override;

    bool initializeFont();
    void beginFrame(const console::ui::Color& clearColor) override;
    void drawPanel(const console::ui::Rect& rect, const console::ui::Color& color, float radius) override;
    void drawText(std::string_view text, console::ui::Vec2 position, float size, const console::ui::Color& color) override;
    void drawIcon(std::string_view icon, console::ui::Vec2 position, float size, const console::ui::Color& color) override;
    void drawLine(console::ui::Vec2 from, console::ui::Vec2 to, float thickness, const console::ui::Color& color) override;
    void endFrame() override;

private:
    SDL_Window* window_{};
    SDL_Renderer* renderer_{};
    TTF_Font* font_{};
    std::string fontPath_;
    float dpiScale_{1.0F};

    static SDL_FColor toSdlColor(const console::ui::Color& color);
    static SDL_FRect toSdlRect(const console::ui::Rect& rect);
    void drawRoundedRect(const SDL_FRect& rect, const SDL_FColor& color, float radius);
};

} // namespace gameos::platform

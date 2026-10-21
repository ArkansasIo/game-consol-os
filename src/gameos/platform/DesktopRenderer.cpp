#include "gameos/platform/DesktopRenderer.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <filesystem>

namespace gameos::platform {

namespace {
std::string findFont() {
    if (const char* env = std::getenv("GAMECONSOL_FONT"); env && *env) {
        if (std::filesystem::exists(env)) return env;
    }
#ifdef _WIN32
    const char* candidates[] = {
        "C:/Windows/Fonts/segoeui.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };
#elif defined(__APPLE__)
    const char* candidates[] = {
        "/System/Library/Fonts/SFNS.ttf",
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "/Library/Fonts/Arial.ttf"
    };
#else
    const char* candidates[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation2/LiberationSans-Regular.ttf"
    };
#endif
    for (const char* path : candidates) {
        if (std::filesystem::exists(path)) return path;
    }
    return {};
}
}

DesktopRenderer::DesktopRenderer(SDL_Window* window, SDL_Renderer* renderer)
    : window_(window), renderer_(renderer) {}

DesktopRenderer::~DesktopRenderer() {
    if (font_) TTF_CloseFont(font_);
}

bool DesktopRenderer::initializeFont() {
    fontPath_ = findFont();
    if (fontPath_.empty()) return false;
    font_ = TTF_OpenFont(fontPath_.c_str(), 28.0F);
    return font_ != nullptr;
}

SDL_FColor DesktopRenderer::toSdlColor(const console::ui::Color& color) {
    return SDL_FColor{color.r, color.g, color.b, color.a};
}

SDL_FRect DesktopRenderer::toSdlRect(const console::ui::Rect& rect) {
    return SDL_FRect{rect.x, rect.y, rect.width, rect.height};
}

void DesktopRenderer::beginFrame(const console::ui::Color& clearColor) {
    SDL_SetRenderDrawColorFloat(renderer_, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    SDL_RenderClear(renderer_);
    int width = 1;
    SDL_GetWindowSizeInPixels(window_, &width, nullptr);
    int logicalWidth = 1;
    SDL_GetWindowSize(window_, &logicalWidth, nullptr);
    if (logicalWidth > 0) dpiScale_ = static_cast<float>(width) / static_cast<float>(logicalWidth);
}

void DesktopRenderer::drawRoundedRect(const SDL_FRect& rect, const SDL_FColor& color, float radius) {
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    const float r = std::clamp(radius, 0.0F, std::min(rect.w, rect.h) * 0.5F);
    SDL_RenderFillRect(renderer_, &SDL_FRect{rect.x + r, rect.y, rect.w - 2.0F * r, rect.h});
    SDL_RenderFillRect(renderer_, &SDL_FRect{rect.x, rect.y + r, rect.w, rect.h - 2.0F * r});
    const int segments = 16;
    for (int corner = 0; corner < 4; ++corner) {
        const float cx = corner % 2 == 0 ? rect.x + r : rect.x + rect.w - r;
        const float cy = corner < 2 ? rect.y + r : rect.y + rect.h - r;
        SDL_RenderPoints(renderer_, nullptr, 0);
        for (int i = 0; i <= segments; ++i) {
            const float a = (static_cast<float>(i) / segments) * 1.57079632679F;
            const float angle = corner == 0 ? 3.14159265359F + a
                              : corner == 1 ? 4.71238898038F + a
                              : corner == 2 ? a
                              : 1.57079632679F + a;
            const float x = cx + std::cos(angle) * r;
            const float y = cy + std::sin(angle) * r;
            SDL_RenderLine(renderer_, cx, cy, x, y);
        }
    }
}

void DesktopRenderer::drawPanel(const console::ui::Rect& rect, const console::ui::Color& color, float radius) {
    drawRoundedRect(toSdlRect(rect), toSdlColor(color), radius);
}

void DesktopRenderer::drawText(std::string_view text, console::ui::Vec2 position, float size, const console::ui::Color& color) {
    if (!font_ || text.empty()) return;
    TTF_SetFontSize(font_, static_cast<int>(std::max(8.0F, size)));
    SDL_Color c{
        static_cast<Uint8>(std::clamp(color.r, 0.0F, 1.0F) * 255.0F),
        static_cast<Uint8>(std::clamp(color.g, 0.0F, 1.0F) * 255.0F),
        static_cast<Uint8>(std::clamp(color.b, 0.0F, 1.0F) * 255.0F),
        static_cast<Uint8>(std::clamp(color.a, 0.0F, 1.0F) * 255.0F)
    };
    SDL_Surface* surface = TTF_RenderText_Blended(font_, std::string(text).c_str(), 0, c);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (texture) {
        SDL_FRect dst{position.x, position.y, static_cast<float>(surface->w), static_cast<float>(surface->h)};
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderTexture(renderer_, texture, nullptr, &dst);
        SDL_DestroyTexture(texture);
    }
    SDL_DestroySurface(surface);
}

void DesktopRenderer::drawIcon(std::string_view icon, console::ui::Vec2 position, float size, const console::ui::Color& color) {
    if (icon.empty()) return;
    drawText(icon, position, size, color);
}

void DesktopRenderer::drawLine(console::ui::Vec2 from, console::ui::Vec2 to, float thickness, const console::ui::Color& color) {
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    const float half = std::max(0.5F, thickness * 0.5F);
    SDL_RenderLine(renderer_, from.x, from.y, to.x, to.y);
    if (thickness > 1.0F) {
        SDL_RenderLine(renderer_, from.x + half, from.y, to.x + half, to.y);
        SDL_RenderLine(renderer_, from.x - half, from.y, to.x - half, to.y);
    }
}

void DesktopRenderer::endFrame() {
    SDL_RenderPresent(renderer_);
}

} // namespace gameos::platform

#include "gameos/platform/DesktopApp.hpp"
#include "gameos/platform/DesktopRenderer.hpp"

#include <SDL3/SDL.h>
#include <chrono>
#include <iostream>

namespace gameos::platform {

struct DesktopApp::State {
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    std::unique_ptr<DesktopRenderer> uiRenderer;
};

DesktopApp::DesktopApp() : state_(std::make_unique<State>()) {
    ui_.shell().setOnActivate([](const console::ui::UiItem& item) {
        std::cout << "Activated: " << item.title << "\n";
    });
}

DesktopApp::~DesktopApp() {
    shutdown();
}

bool DesktopApp::initialize() {
    if (running_) return true;
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_EVENTS)) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << "\n";
        return false;
    }
    if (!TTF_Init()) {
        std::cerr << "SDL_ttf initialization failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    state_->window = SDL_CreateWindow(
        "GameConsolOS",
        1440,
        900,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
    );
    if (!state_->window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
        shutdown();
        return false;
    }

    state_->renderer = SDL_CreateRenderer(state_->window, nullptr);
    if (!state_->renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << "\n";
        shutdown();
        return false;
    }
    SDL_SetRenderVSync(state_->renderer, 1);
    state_->uiRenderer = std::make_unique<DesktopRenderer>(state_->window, state_->renderer);
    if (!state_->uiRenderer->initializeFont()) {
        std::cerr << "Warning: no desktop font found; text will be hidden. Set GAMECONSOL_FONT to a TTF file.\n";
    }
    running_ = true;
    return true;
}

void DesktopApp::processEvents() {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running_ = false;
            continue;
        }
        if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
            using D = console::ui::Direction;
            switch (event.key.key) {
                case SDLK_LEFT: ui_.shell().move(D::Left); break;
                case SDLK_RIGHT: ui_.shell().move(D::Right); break;
                case SDLK_UP: ui_.shell().move(D::Up); break;
                case SDLK_DOWN: ui_.shell().move(D::Down); break;
                case SDLK_RETURN:
                case SDLK_SPACE: ui_.shell().activate(); break;
                case SDLK_ESCAPE: ui_.shell().back(); break;
                case SDLK_Q: running_ = false; break;
                default: break;
            }
        }
        if (event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
            using D = console::ui::Direction;
            switch (event.gbutton.button) {
                case SDL_GAMEPAD_BUTTON_DPAD_LEFT: ui_.shell().move(D::Left); break;
                case SDL_GAMEPAD_BUTTON_DPAD_RIGHT: ui_.shell().move(D::Right); break;
                case SDL_GAMEPAD_BUTTON_DPAD_UP: ui_.shell().move(D::Up); break;
                case SDL_GAMEPAD_BUTTON_DPAD_DOWN: ui_.shell().move(D::Down); break;
                case SDL_GAMEPAD_BUTTON_SOUTH: ui_.shell().activate(); break;
                case SDL_GAMEPAD_BUTTON_EAST: ui_.shell().back(); break;
                default: break;
            }
        }
    }
}

void DesktopApp::render() {
    int width = 1440;
    int height = 900;
    SDL_GetWindowSize(state_->window, &width, &height);
    ui_.render(*state_->uiRenderer, static_cast<float>(width), static_cast<float>(height));
}

int DesktopApp::run(bool headless) {
    if (headless) {
        ui_.tick(0.016F);
        return 0;
    }
    if (!running_ && !initialize()) return 1;

    auto previous = std::chrono::steady_clock::now();
    while (running_) {
        processEvents();
        const auto now = std::chrono::steady_clock::now();
        const float delta = std::chrono::duration<float>(now - previous).count();
        previous = now;
        ui_.tick(delta);
        render();
    }
    return 0;
}

void DesktopApp::shutdown() {
    state_->uiRenderer.reset();
    if (state_->renderer) {
        SDL_DestroyRenderer(state_->renderer);
        state_->renderer = nullptr;
    }
    if (state_->window) {
        SDL_DestroyWindow(state_->window);
        state_->window = nullptr;
    }
    if (TTF_WasInit()) TTF_Quit();
    SDL_Quit();
    running_ = false;
}

} // namespace gameos::platform

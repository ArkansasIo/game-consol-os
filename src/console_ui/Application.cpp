#include "console_ui/UI.hpp"

namespace console::ui {

Application::Application() {
    shell_.addItem({"games", "Games", "Launch and manage installed games", "GAME", Screen::Games});
    shell_.addItem({"media", "Media", "Music, video, captures and streaming", "MEDIA", Screen::Media});
    shell_.addItem({"library", "Library", "Installed applications and content", "LIB", Screen::Library});
    shell_.addItem({"store", "Store", "Discover downloadable content", "STORE", Screen::Store});
    shell_.addItem({"profile", "Profile", "Account, friends and achievements", "USER", Screen::Profile});
    shell_.addItem({"settings", "Settings", "System, controller and display options", "SET", Screen::Settings});
}

void Application::tick(float deltaSeconds) {
    shell_.tick(deltaSeconds);
}

void Application::render(IRenderer& renderer, float width, float height) const {
    shell_.render(renderer, width, height);
}

} // namespace console::ui

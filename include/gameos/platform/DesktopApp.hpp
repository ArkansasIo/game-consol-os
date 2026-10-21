#pragma once

#include "console_ui/UI.hpp"
#include <memory>

namespace gameos::platform {

class DesktopRenderer;

class DesktopApp {
public:
    DesktopApp();
    ~DesktopApp();

    DesktopApp(const DesktopApp&) = delete;
    DesktopApp& operator=(const DesktopApp&) = delete;

    bool initialize();
    int run(bool headless = false);
    void shutdown();

    [[nodiscard]] bool running() const noexcept { return running_; }
    [[nodiscard]] console::ui::Application& ui() noexcept { return ui_; }

private:
    struct State;
    std::unique_ptr<State> state_;
    console::ui::Application ui_;
    bool running_{false};

    void processEvents();
    void render();
};

} // namespace gameos::platform

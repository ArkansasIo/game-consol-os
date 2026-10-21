#include "gameos/platform/DesktopApp.hpp"

#include <string_view>

int main(int argc, char** argv) {
    bool headless = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string_view(argv[i]) == "--headless") headless = true;
    }

    gameos::platform::DesktopApp app;
    if (headless) return app.run(true);
    return app.run(false);
}

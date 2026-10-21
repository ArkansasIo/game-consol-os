#include "gameos/app/ApplicationServices.hpp"
#include "gameos/settings/SettingsManager.hpp"
#include "gameos/system/SystemServices.hpp"
#include "gameos/input/InputManager.hpp"
#include "gameos/audio/AudioManager.hpp"
#include <cassert>
#include <filesystem>

int main() {
    gameos::app::ApplicationRegistry registry;
    assert(registry.install({"games.demo", "Demo Game", "1.0.0", "demo"}));
    assert(registry.contains("games.demo"));
    gameos::app::LauncherService launcher(registry);
    assert(launcher.launch("games.demo"));
    assert(launcher.activeApp() == "games.demo");
    assert(launcher.close("games.demo"));

    gameos::settings::SettingsManager settings;
    settings.setBool("fullscreen", true);
    settings.setInt("volume", 80);
    const auto path = (std::filesystem::temp_directory_path() / "gameconsolos-test.cfg").string();
    assert(settings.save(path));
    gameos::settings::SettingsManager loaded;
    assert(loaded.load(path));
    assert(loaded.getBool("fullscreen"));
    assert(loaded.getInt("volume") == 80);
    std::filesystem::remove(path);

    gameos::system::NotificationCenter notifications;
    bool received = false;
    notifications.subscribe([&](const auto&) { received = true; });
    notifications.push({"Test", "Hello", false});
    assert(received && notifications.notifications().size() == 1);

    gameos::input::InputManager input;
    bool invoked = false;
    input.bind(gameos::input::Action::Confirm, [&](auto) { invoked = true; });
    input.dispatch(gameos::input::Action::Confirm);
    assert(invoked);

    gameos::audio::AudioManager audio;
    assert(audio.initialize());
    audio.setMasterVolume(0.5F);
    assert(audio.masterVolume() == 0.5F);
    audio.shutdown();
    return 0;
}

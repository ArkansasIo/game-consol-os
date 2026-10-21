#pragma once
#include <string>
#include <unordered_map>

namespace gameos::audio {
class AudioManager {
public:
    bool initialize();
    void shutdown();
    void setMasterVolume(float value) noexcept;
    void setMusicVolume(float value) noexcept;
    void setEffectsVolume(float value) noexcept;
    void playUiSound(const std::string& id);
    [[nodiscard]] float masterVolume() const noexcept { return master_; }
    [[nodiscard]] float musicVolume() const noexcept { return music_; }
    [[nodiscard]] float effectsVolume() const noexcept { return effects_; }
private:
    float master_{1.0F}; float music_{1.0F}; float effects_{1.0F}; bool initialized_{false};
};
} // namespace gameos::audio

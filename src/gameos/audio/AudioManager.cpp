#include "gameos/audio/AudioManager.hpp"
#include <algorithm>
#include <iostream>
namespace gameos::audio {
bool AudioManager::initialize() { initialized_ = true; return true; }
void AudioManager::shutdown() { initialized_ = false; }
void AudioManager::setMasterVolume(float value) noexcept { master_ = std::clamp(value, 0.0F, 1.0F); }
void AudioManager::setMusicVolume(float value) noexcept { music_ = std::clamp(value, 0.0F, 1.0F); }
void AudioManager::setEffectsVolume(float value) noexcept { effects_ = std::clamp(value, 0.0F, 1.0F); }
void AudioManager::playUiSound(const std::string& id) { if (initialized_) std::clog << "UI sound: " << id << '\n'; }
} // namespace gameos::audio

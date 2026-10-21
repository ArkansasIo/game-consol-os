#include "gameos/settings/SettingsManager.hpp"
#include <fstream>
#include <sstream>

namespace gameos::settings {
void SettingsManager::set(std::string key, std::string value) { values_[std::move(key)] = std::move(value); }
void SettingsManager::setBool(const std::string& key, bool value) { set(key, value ? "true" : "false"); }
void SettingsManager::setInt(const std::string& key, long long value) { set(key, std::to_string(value)); }
std::string SettingsManager::get(const std::string& key, const std::string& fallback) const {
    const auto it = values_.find(key); return it == values_.end() ? fallback : it->second;
}
bool SettingsManager::getBool(const std::string& key, bool fallback) const {
    const auto value = get(key, fallback ? "true" : "false"); return value == "true" || value == "1" || value == "yes";
}
long long SettingsManager::getInt(const std::string& key, long long fallback) const {
    try { return std::stoll(get(key, std::to_string(fallback))); } catch (...) { return fallback; }
}
bool SettingsManager::save(const std::string& path) const {
    std::ofstream out(path, std::ios::trunc); if (!out) return false;
    for (const auto& [key, value] : values_) out << key << '=' << value << '\n';
    return static_cast<bool>(out);
}
bool SettingsManager::load(const std::string& path) {
    std::ifstream in(path); if (!in) return false;
    std::string line;
    while (std::getline(in, line)) {
        const auto pos = line.find('='); if (pos == std::string::npos) continue;
        set(line.substr(0, pos), line.substr(pos + 1));
    }
    return true;
}
} // namespace gameos::settings

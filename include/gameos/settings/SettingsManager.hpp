#pragma once
#include <string>
#include <unordered_map>

namespace gameos::settings {

class SettingsManager {
public:
    void set(std::string key, std::string value);
    void setBool(const std::string& key, bool value);
    void setInt(const std::string& key, long long value);
    [[nodiscard]] std::string get(const std::string& key, const std::string& fallback = {}) const;
    [[nodiscard]] bool getBool(const std::string& key, bool fallback = false) const;
    [[nodiscard]] long long getInt(const std::string& key, long long fallback = 0) const;
    bool save(const std::string& path) const;
    bool load(const std::string& path);
private:
    std::unordered_map<std::string, std::string> values_;
};

} // namespace gameos::settings

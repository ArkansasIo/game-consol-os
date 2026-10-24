#include "gameos/core/ConfigStore.hpp"
#include <fstream>
namespace gameos::core {

bool ConfigStore::load(const std::string& path) {
    std::ifstream in(path);
    if (!in) return false;
    values_.clear();
    std::string line;
    while (std::getline(in, line)) {
        auto pos = line.find('=');
        if (pos != std::string::npos)
            values_[line.substr(0, pos)] = line.substr(pos + 1);
    }
    return true;
}

bool ConfigStore::save(const std::string& path) const {
    std::ofstream out(path);
    if (!out) return false;
    for (auto& [key, value] : values_)
        out << key << '=' << value << '\n';
    return true;
}

void ConfigStore::set(std::string key, std::string value) {
    values_[std::move(key)] = std::move(value);
}

std::string ConfigStore::get(const std::string& key, const std::string& fallback) const {
    auto it = values_.find(key);
    return it == values_.end() ? fallback : it->second;
}

} // namespace gameos::core

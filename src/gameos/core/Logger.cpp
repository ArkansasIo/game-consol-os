#include "gameos/core/Logger.hpp"
#include <filesystem>
#include <iostream>
namespace gameos::core {

void Logger::log(LogLevel level, std::string_view message) {
    std::scoped_lock lock(mutex_);
    std::filesystem::path path(file_);
    std::error_code ec;
    std::filesystem::create_directories(path.parent_path(), ec);
    std::ofstream out(file_, std::ios::app);
    static const char* names[] = {"DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"};
    auto index = static_cast<int>(level);
    if (out) out << names[index] << ' ' << message << '\n';
    std::clog << names[index] << ' ' << message << '\n';
}

} // namespace gameos::core

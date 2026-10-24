#include "gameos/core/VirtualFileSystem.hpp"
#include <fstream>
namespace gameos::core {

std::filesystem::path VirtualFileSystem::resolve(const std::filesystem::path& relative) const {
    return (root_ / relative).lexically_normal();
}

bool VirtualFileSystem::exists(const std::filesystem::path& relative) const {
    return std::filesystem::exists(resolve(relative));
}

bool VirtualFileSystem::writeText(const std::filesystem::path& relative, const std::string& text) {
    auto path = resolve(relative);
    std::error_code ec;
    std::filesystem::create_directories(path.parent_path(), ec);
    if (ec) return false;
    std::ofstream out(path);
    if (!out) return false;
    out << text;
    return static_cast<bool>(out);
}

std::optional<std::string> VirtualFileSystem::readText(const std::filesystem::path& relative) const {
    std::ifstream in(resolve(relative));
    if (!in) return std::nullopt;
    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

} // namespace gameos::core

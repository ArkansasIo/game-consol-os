#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace gameos::app {

enum class AppState { Running, Suspended, Stopped };

struct AppDescriptor {
    std::string id;
    std::string name;
    std::string version;
    std::string executable;
    bool pinned{false};
};

class ApplicationRegistry {
public:
    bool install(AppDescriptor app);
    bool remove(const std::string& id);
    bool contains(const std::string& id) const;
    const AppDescriptor* find(const std::string& id) const;
    const std::vector<AppDescriptor>& applications() const noexcept { return apps_; }
    void sortByName();
private:
    std::vector<AppDescriptor> apps_;
};

class LauncherService {
public:
    using LaunchCallback = std::function<bool(const AppDescriptor&)>;
    explicit LauncherService(ApplicationRegistry& registry) : registry_(registry) {}
    void setCallback(LaunchCallback callback) { callback_ = std::move(callback); }
    bool launch(const std::string& id);
    bool close(const std::string& id);
    [[nodiscard]] const std::string& activeApp() const noexcept { return active_; }
private:
    ApplicationRegistry& registry_;
    LaunchCallback callback_;
    std::string active_;
};

} // namespace gameos::app

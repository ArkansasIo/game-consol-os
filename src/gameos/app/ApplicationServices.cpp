#include "gameos/app/ApplicationServices.hpp"
#include <algorithm>

namespace gameos::app {

bool ApplicationRegistry::install(AppDescriptor app) {
    if (app.id.empty() || contains(app.id)) return false;
    apps_.push_back(std::move(app));
    return true;
}

bool ApplicationRegistry::remove(const std::string& id) {
    const auto oldSize = apps_.size();
    apps_.erase(std::remove_if(apps_.begin(), apps_.end(), [&](const auto& app) { return app.id == id; }), apps_.end());
    return apps_.size() != oldSize;
}

bool ApplicationRegistry::contains(const std::string& id) const {
    return find(id) != nullptr;
}

const AppDescriptor* ApplicationRegistry::find(const std::string& id) const {
    const auto it = std::find_if(apps_.begin(), apps_.end(), [&](const auto& app) { return app.id == id; });
    return it == apps_.end() ? nullptr : &*it;
}

void ApplicationRegistry::sortByName() {
    std::sort(apps_.begin(), apps_.end(), [](const auto& a, const auto& b) { return a.name < b.name; });
}

bool LauncherService::launch(const std::string& id) {
    const auto* app = registry_.find(id);
    if (!app) return false;
    if (callback_ && !callback_(*app)) return false;
    active_ = id;
    return true;
}

bool LauncherService::close(const std::string& id) {
    if (active_ != id) return false;
    active_.clear();
    return true;
}

} // namespace gameos::app

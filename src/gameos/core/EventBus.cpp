#include "gameos/core/EventBus.hpp"
#include <algorithm>
namespace gameos::core {

std::size_t EventBus::subscribe(const std::string& type, Handler handler) {
    std::scoped_lock lock(mutex_);
    auto token = nextToken_++;
    handlers_[type].push_back({token, std::move(handler)});
    return token;
}

void EventBus::unsubscribe(const std::string& type, std::size_t token) {
    std::scoped_lock lock(mutex_);
    auto found = handlers_.find(type);
    if (found == handlers_.end()) return;
    auto& slots = found->second;
    slots.erase(std::remove_if(slots.begin(), slots.end(),
                               [&](const Slot& slot) { return slot.token == token; }),
                slots.end());
}

void EventBus::publish(const std::string& type, const std::string& payload) {
    std::vector<Handler> snapshot;
    {
        std::scoped_lock lock(mutex_);
        auto found = handlers_.find(type);
        if (found != handlers_.end())
            for (auto& slot : found->second) snapshot.push_back(slot.handler);
    }
    for (auto& handler : snapshot) handler(payload);
}

} // namespace gameos::core

#include "gameos/system/SystemServices.hpp"
namespace gameos::system {
void NotificationCenter::push(Notification notification) {
    for (auto& listener : listeners_) listener(notification);
    notifications_.push_back(std::move(notification));
}
void NotificationCenter::subscribe(Listener listener) { listeners_.push_back(std::move(listener)); }
void NotificationCenter::clear() { notifications_.clear(); }
} // namespace gameos::system

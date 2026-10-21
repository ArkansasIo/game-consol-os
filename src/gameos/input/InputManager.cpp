#include "gameos/input/InputManager.hpp"
namespace gameos::input {
void InputManager::dispatch(Action action) const {
    const auto it = handlers_.find(action);
    if (it != handlers_.end() && it->second) it->second(action);
}
} // namespace gameos::input

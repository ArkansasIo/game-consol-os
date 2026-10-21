#pragma once
#include <functional>
#include <string>
#include <unordered_map>

namespace gameos::input {
enum class Action { Up, Down, Left, Right, Confirm, Back, Menu, Screenshot, Pause };
class InputManager {
public:
    using Handler = std::function<void(Action)>;
    void bind(Action action, Handler handler) { handlers_[action] = std::move(handler); }
    void dispatch(Action action) const;
    void setControllerName(std::string name) { controllerName_ = std::move(name); }
    [[nodiscard]] const std::string& controllerName() const noexcept { return controllerName_; }
private:
    std::unordered_map<Action, Handler> handlers_;
    std::string controllerName_;
};
} // namespace gameos::input

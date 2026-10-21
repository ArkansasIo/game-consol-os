#include "console_ui/UI.hpp"

#include <utility>

namespace console::ui {

void InputRouter::setCallback(Callback callback) {
    callback_ = std::move(callback);
}

void InputRouter::submit(Direction direction) {
    if (callback_) callback_(direction);
}

} // namespace console::ui

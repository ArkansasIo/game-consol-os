#pragma once
#include <functional>
#include <string>
#include <vector>

namespace gameos::system {

enum class PowerAction { Lock, Sleep, Restart, Shutdown, ExitApplication };

class NotificationCenter {
public:
    struct Notification { std::string title; std::string message; bool persistent{false}; };
    using Listener = std::function<void(const Notification&)>;
    void push(Notification notification);
    void subscribe(Listener listener);
    void clear();
    [[nodiscard]] const std::vector<Notification>& notifications() const noexcept { return notifications_; }
private:
    std::vector<Notification> notifications_;
    std::vector<Listener> listeners_;
};

class PowerManager {
public:
    using Callback = std::function<void(PowerAction)>;
    void setCallback(Callback callback) { callback_ = std::move(callback); }
    void request(PowerAction action) const { if (callback_) callback_(action); }
private:
    Callback callback_;
};

class ClipboardService {
public:
    void setText(std::string text) { text_ = std::move(text); }
    [[nodiscard]] const std::string& text() const noexcept { return text_; }
private:
    std::string text_;
};

} // namespace gameos::system

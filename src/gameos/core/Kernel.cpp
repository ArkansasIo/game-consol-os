#include "gameos/core/Kernel.hpp"
namespace gameos::core {

bool Kernel::boot(BootConfig config) {
    config_ = std::move(config);
    for (auto* subsystem : subsystems_) {
        if (!subsystem->start(config_)) {
            panic(std::string("Failed to start subsystem: ") + subsystem->name());
            return false;
        }
    }
    frame_ = 0;
    running_ = true;
    return true;
}

void Kernel::runFrame(double dt) {
    if (!running_) return;
    TickContext context{dt, ++frame_};
    for (auto* subsystem : subsystems_) subsystem->tick(context);
}

void Kernel::shutdown() noexcept {
    if (!running_) return;
    for (auto it = subsystems_.rbegin(); it != subsystems_.rend(); ++it)
        (*it)->stop();
    running_ = false;
}

void Kernel::addSubsystem(ISubsystem& subsystem) {
    if (!running_) subsystems_.push_back(&subsystem);
}

void Kernel::setPanicHandler(PanicHandler handler) {
    panicHandler_ = std::move(handler);
}

void Kernel::panic(const std::string& message) {
    if (panicHandler_) panicHandler_(message);
}

} // namespace gameos::core

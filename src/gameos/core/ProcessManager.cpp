#include "gameos/core/ProcessManager.hpp"
namespace gameos::core {

void ProcessManager::tick(const TickContext&) {
    if (!running_) return;
    for (auto& [id, process] : processes_) {
        if (process.state == ProcessState::Running && process.entry) {
            process.exitCode = process.entry();
            process.state = ProcessState::Stopped;
        }
    }
}

ProcessId ProcessManager::spawn(std::string name, std::function<int()> entry) {
    auto id = nextId_++;
    processes_.emplace(id, Process{id, std::move(name), ProcessState::Running, std::move(entry), 0});
    return id;
}

bool ProcessManager::suspend(ProcessId id) {
    auto found = processes_.find(id);
    if (found == processes_.end() || found->second.state != ProcessState::Running) return false;
    found->second.state = ProcessState::Suspended;
    return true;
}

bool ProcessManager::resume(ProcessId id) {
    auto found = processes_.find(id);
    if (found == processes_.end() || found->second.state != ProcessState::Suspended) return false;
    found->second.state = ProcessState::Running;
    return true;
}

bool ProcessManager::terminate(ProcessId id, int code) {
    auto found = processes_.find(id);
    if (found == processes_.end()) return false;
    found->second.exitCode = code;
    found->second.state = ProcessState::Stopped;
    return true;
}

const Process* ProcessManager::find(ProcessId id) const {
    auto found = processes_.find(id);
    return found == processes_.end() ? nullptr : &found->second;
}

} // namespace gameos::core

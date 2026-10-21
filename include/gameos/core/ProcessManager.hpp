#pragma once
#include "gameos/core/Kernel.hpp"
#include <functional>
#include <string>
#include <unordered_map>
namespace gameos::core { enum class ProcessState{Created,Running,Suspended,Stopped,Failed}; struct Process{ProcessId id{};std::string name;ProcessState state{ProcessState::Created};std::function<int()>entry;int exitCode{};}; class ProcessManager:public ISubsystem{public:const char*name()const noexcept override{return "ProcessManager";}bool start(const BootConfig&)override{running_=true;return true;}void tick(const TickContext&)override;void stop()noexcept override{running_=false;processes_.clear();}ProcessId spawn(std::string,std::function<int()>);bool suspend(ProcessId);bool resume(ProcessId);bool terminate(ProcessId,int=0);const Process*find(ProcessId)const;private:bool running_{};ProcessId nextId_{1};std::unordered_map<ProcessId,Process>processes_;}; }

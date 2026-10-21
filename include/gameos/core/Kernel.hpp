#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
namespace gameos::core { using ProcessId=std::uint32_t; using ServiceId=std::uint32_t; struct BootConfig{std::string build;std::string dataRoot{"data"};bool safeMode{false};}; struct TickContext{double deltaSeconds{};std::uint64_t frame{};}; class ISubsystem{public:virtual~ISubsystem()=default;virtual const char*name()const noexcept=0;virtual bool start(const BootConfig&)=0;virtual void tick(const TickContext&)=0;virtual void stop()noexcept=0;}; class Kernel{public:using PanicHandler=std::function<void(const std::string&)>;bool boot(BootConfig={});void runFrame(double);void shutdown()noexcept;void addSubsystem(ISubsystem&);void setPanicHandler(PanicHandler);bool running()const noexcept{return running_;}std::uint64_t frame()const noexcept{return frame_;}void panic(const std::string&);private:BootConfig config_{};std::vector<ISubsystem*>subsystems_{};PanicHandler panicHandler_{};std::uint64_t frame_{};bool running_{};}; }

#pragma once
#include "gameos/core/Kernel.hpp"
#include <fstream>
#include <mutex>
#include <string>
#include <string_view>
namespace gameos::core{enum class LogLevel{Debug,Info,Warning,Error,Critical};class Logger:public ISubsystem{public:explicit Logger(std::string f="logs/gameos.log"):file_(std::move(f)){}const char*name()const noexcept override{return "Logger";}bool start(const BootConfig&)override{return true;}void tick(const TickContext&)override{}void stop()noexcept override{}void log(LogLevel,std::string_view);private:std::mutex mutex_;std::string file_;};}

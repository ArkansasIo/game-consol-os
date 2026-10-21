#pragma once
#include "gameos/core/Kernel.hpp"
#include <filesystem>
#include <optional>
#include <string>
namespace gameos::core{class VirtualFileSystem:public ISubsystem{public:const char*name()const noexcept override{return "VirtualFileSystem";}bool start(const BootConfig&c)override{root_=c.dataRoot;std::error_code e;std::filesystem::create_directories(root_,e);return !e;}void tick(const TickContext&)override{}void stop()noexcept override{}std::filesystem::path resolve(const std::filesystem::path&)const;bool exists(const std::filesystem::path&)const;bool writeText(const std::filesystem::path&,const std::string&);std::optional<std::string>readText(const std::filesystem::path&)const;private:std::filesystem::path root_{"data"};};}

#include "gameos/core/Logger.hpp"
#include <filesystem>
#include <iostream>
namespace gameos::core{void Logger::log(LogLevel l,std::string_view m){std::scoped_lock lock(mutex_);std::filesystem::path p(file_);std::error_code e;std::filesystem::create_directories(p.parent_path(),e);std::ofstream o(file_,std::ios::app);const char*n[]={"DEBUG","INFO","WARN","ERROR","CRITICAL"};auto i=static_cast<int>(l);if(o)o<<n[i]<<' '<<m<<'\n';std::clog<<n[i]<<' '<<m<<'\n';}}

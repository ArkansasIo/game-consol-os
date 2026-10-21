#pragma once
#include <string>
#include <unordered_map>
namespace gameos::core{class ConfigStore{public:bool load(const std::string&);bool save(const std::string&)const;void set(std::string,std::string);std::string get(const std::string&,const std::string&={})const;private:std::unordered_map<std::string,std::string>values_;};}

#pragma once
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>
namespace gameos::core { class EventBus{public:using Handler=std::function<void(const std::string&)>;std::size_t subscribe(const std::string&,Handler);void unsubscribe(const std::string&,std::size_t);void publish(const std::string&,const std::string&={});private:struct Slot{std::size_t token;Handler handler;};std::mutex mutex_;std::size_t nextToken_{1};std::unordered_map<std::string,std::vector<Slot>>handlers_;}; }

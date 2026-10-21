#pragma once
#include "gameos/gui/Gui.hpp"
#include <memory>
#include <string>
#include <vector>
namespace gameos::gui{struct Window{std::uint32_t id{};std::string title;Rect rect;bool visible{true};std::shared_ptr<Scene>scene;};class WindowManager{public:std::uint32_t create(std::string,Rect);bool close(std::uint32_t);Window*find(std::uint32_t);void update(double);void draw(Canvas&)const;bool dispatch(Event);private:std::uint32_t nextId_{1};std::vector<Window>windows_;};}

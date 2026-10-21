#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>
namespace gameos::gui{struct Vec2{float x{},y{};};struct Rect{float x{},y{},w{},h{};};struct Color{float r{},g{},b{},a{1};};enum class EventType{PointerDown,PointerUp,PointerMove,KeyDown,KeyUp,Focus,Blur,Activate};struct Event{EventType type;int key{};Vec2 pointer{};bool handled{false};};class Canvas{public:virtual~Canvas()=default;virtual void panel(Rect,Color,float)=0;virtual void text(Vec2,const std::string&,Color,float)=0;virtual void image(Rect,const std::string&,float)=0;virtual void line(Vec2,Vec2,Color,float)=0;};class Widget{public:virtual~Widget()=default;virtual void update(double)=0;virtual void draw(Canvas&)const=0;virtual bool handle(Event&)=0;void setBounds(Rect r){bounds_=r;}Rect bounds()const{return bounds_;}void setVisible(bool v){visible_=v;}bool visible()const{return visible_;}private:Rect bounds_{};bool visible_{true};};class Scene{public:void add(std::shared_ptr<Widget>);void update(double);void draw(Canvas&)const;bool dispatch(Event);private:std::vector<std::shared_ptr<Widget>>widgets_;};}

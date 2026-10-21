#include "gameos/core/Kernel.hpp"
#include "gameos/core/EventBus.hpp"
#include "gameos/core/ProcessManager.hpp"
#include "gameos/update/UpdateManager.hpp"
#include "gameos/gui/Gui.hpp"
#include <cassert>
#include <memory>
int main(){using namespace gameos::core;Kernel k;ProcessManager pm;k.addSubsystem(pm);assert(k.boot());auto id=pm.spawn("demo",[]{return 7;});k.runFrame(.016);assert(pm.find(id)->state==ProcessState::Stopped);k.shutdown();EventBus b;int hits=0;auto t=b.subscribe("ui",[&](const std::string&){++hits;});b.publish("ui","activate");assert(hits==1);b.unsubscribe("ui",t);gameos::update::UpdateManager u;assert(u.validate({"demo","1.0","1.0"}));gameos::gui::Scene s;s.update(.016);return 0;}

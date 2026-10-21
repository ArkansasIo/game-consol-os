#include "console_ui/UI.hpp"

#include <cassert>
#include <string>

int main() {
    using namespace console::ui;

    XmbShell shell;
    shell.addItem({"one", "One", "First", "1", Screen::Games});
    shell.addItem({"two", "Two", "Second", "2", Screen::Media});
    shell.addItem({"three", "Three", "Third", "3", Screen::Settings});

    assert(shell.selectedIndex() == 0);
    shell.move(Direction::Right);
    assert(shell.selectedIndex() == 1);
    shell.move(Direction::Right);
    assert(shell.selectedIndex() == 2);
    shell.move(Direction::Left);
    assert(shell.selectedIndex() == 1);

    bool activated = false;
    shell.setOnActivate([&activated](const UiItem& item) {
        activated = item.id == "two";
    });
    shell.activate();
    assert(activated);
    assert(shell.screen() == Screen::Media);

    Animation animation{.duration = 1.0F, .elapsed = 0.0F, .easing = Easing::Linear};
    float progress = 0.0F;
    animation.update = [&progress](float value) { progress = value; };
    animation.tick(0.5F);
    assert(progress > 0.49F && progress < 0.51F);
    animation.tick(0.5F);
    assert(animation.finished());
    assert(progress == 1.0F);

    return 0;
}

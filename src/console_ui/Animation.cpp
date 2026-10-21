#include "console_ui/UI.hpp"

#include <algorithm>
#include <cmath>

namespace console::ui {

namespace {
float curve(Easing easing, float t) {
    t = std::clamp(t, 0.0F, 1.0F);
    switch (easing) {
    case Easing::Linear: return t;
    case Easing::EaseOutCubic: {
        const float u = 1.0F - t;
        return 1.0F - u * u * u;
    }
    case Easing::EaseInOutCubic:
        return t < 0.5F ? 4.0F * t * t * t : 1.0F - std::pow(-2.0F * t + 2.0F, 3.0F) / 2.0F;
    }
    return t;
}
}

void Animation::tick(float deltaSeconds) {
    if (duration <= 0.0F) {
        elapsed = duration;
        if (update) update(1.0F);
        return;
    }
    elapsed = std::min(duration, elapsed + std::max(0.0F, deltaSeconds));
    if (update) update(curve(easing, elapsed / duration));
}

} // namespace console::ui

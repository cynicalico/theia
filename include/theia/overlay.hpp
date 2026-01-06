#pragma once

#include "theia/hermes.hpp"

namespace theia {
struct OverlayTabEvent {
    MAKE_HERMES_ID(theia::OverlayTabEvent);
};

void draw_overlay();
} // namespace theia

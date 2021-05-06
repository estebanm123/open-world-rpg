#pragma once

#include "SingleHitbox.h"

// It's really just a trapezoid
struct ViewCone : public SingleHitbox {
    // Assumes botWidth > topWidth
    ViewCone(sf::Vector2f globalConePos, float botWidth, float topWidth, float height);
};





#pragma once

// Defines constraints for common actions performed by partition slots
#include "ActiveZone.h"

struct ActiveZones {
    ActiveZone renderZone;
    ActiveZone collisionZone;

    ActiveZones(sf::Vector2f playerPos, sf::Vector2i renderZoneSize, sf::Vector2i collisionZoneSize);

    void updateZones(float dt, sf::Vector2f playerPos);
};



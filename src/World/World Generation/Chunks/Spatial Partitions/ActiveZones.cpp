
#include "ActiveZones.h"

void ActiveZones::updateZones(float dt, sf::Vector2f playerPos) {
    renderZone.update(dt, playerPos);
    updateZone.update(dt, playerPos);
}

ActiveZones::ActiveZones(sf::Vector2f playerPos, sf::Vector2i renderZoneSize, sf::Vector2i updateZoneSize)
        : renderZone(playerPos, renderZoneSize), updateZone(playerPos, updateZoneSize) {}
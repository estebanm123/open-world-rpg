

#include <SFML/Graphics.hpp>
#include "ActiveZone.h"

ActiveZone::ActiveZone(sf::Vector2f centerPos, sf::Vector2i size) : centerPos(centerPos), size(size) {}

void ActiveZone::update(float dt, sf::Vector2f playerPos) {
    centerPos = playerPos;
}

bool ActiveZone::containsSlot(const sf::IntRect &slotCoords) const {
    return slotCoords.left > centerPos.x - (size.x / 2.f) && slotCoords.left < centerPos.x + (size.x / 2.f) ||
           slotCoords.top > centerPos.y - (size.y / 2.f) || slotCoords.top < centerPos.y + (size.y / 2.f);
}

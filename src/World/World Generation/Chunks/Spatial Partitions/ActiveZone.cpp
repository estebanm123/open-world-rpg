

#include <SFML/Graphics.hpp>
#include "ActiveZone.h"

ActiveZone::ActiveZone(sf::Vector2f centerPos, sf::Vector2i size) : centerPos(centerPos), size(size) {}

void ActiveZone::update(float dt, sf::Vector2f playerPos) {
    centerPos = playerPos;
}

bool ActiveZone::containsSlot(sf::Vector2f slotTopLeftCoords, sf::Vector2i slotSize) const {
    return slotTopLeftCoords.x > centerPos.x - (size.x / 2.f) &&
           slotTopLeftCoords.x + slotSize.x < centerPos.x + (size.x / 2.f) ||
           slotTopLeftCoords.y > centerPos.y - (size.y / 2.f) ||
           slotTopLeftCoords.y + slotSize.y < centerPos.y + (size.y / 2.f);
}

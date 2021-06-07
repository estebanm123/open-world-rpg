

#include "ActiveZone.h"

#include <SFML/Graphics.hpp>

#include "SpatialPartition.h"

inline const auto SLOT_SIZE = sf::Vector2i{SpatialPartition::SLOT_WIDTH, SpatialPartition::SLOT_HEIGHT};

ActiveZone::ActiveZone(sf::Vector2f centerPos, sf::Vector2i size)
	: centerPos(centerPos),
	  sizeInPx({size.x * static_cast<float>(SpatialPartition::SLOT_WIDTH),
				size.y * static_cast<float>(SpatialPartition::SLOT_HEIGHT)}) {}

void ActiveZone::update(float dt, sf::Vector2f playerPos) { centerPos = playerPos; }

bool ActiveZone::containsSlot(sf::Vector2f slotTopLeftCoords, sf::Vector2i slotSize) const {
	return slotTopLeftCoords.x > centerPos.x - (sizeInPx.x / 2.f) &&
		   slotTopLeftCoords.x + slotSize.x < centerPos.x + (sizeInPx.x / 2.f) &&
		   slotTopLeftCoords.y > centerPos.y - (sizeInPx.y / 2.f) &&
		   slotTopLeftCoords.y + slotSize.y < centerPos.y + (sizeInPx.y / 2.f);
}

const sf::Vector2f &ActiveZone::getCenterPos() const { return centerPos; }

const sf::Vector2f &ActiveZone::getSize() const { return sizeInPx; }

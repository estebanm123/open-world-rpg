#pragma once

#include <SFML/Graphics.hpp>

class PartitionSlot;

class ActiveZone {
public:
	ActiveZone(sf::Vector2f centerPos, sf::Vector2i sizeInSlots);

	void update(float dt, sf::Vector2f playerPos);

	bool containsSlot(sf::Vector2f slotTopLeftCoords, sf::Vector2i slotSize) const;

private:
	sf::Vector2f centerPos;
	sf::Vector2f sizeInPx;

public:
	const sf::Vector2f &getCenterPos() const;

	const sf::Vector2f &getSize() const;
};

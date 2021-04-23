#pragma once

#include <SFML/Graphics.hpp>

class PartitionSlot;

class ActiveZone {
public:
    ActiveZone(sf::Vector2f centerPos, sf::Vector2i size);

    void update(float dt, sf::Vector2f playerPos);

    bool containsSlot(sf::Vector2f slotTopLeftCoords, sf::Vector2i slotSize) const;

private:
    sf::Vector2f centerPos;
    sf::Vector2i size;
};





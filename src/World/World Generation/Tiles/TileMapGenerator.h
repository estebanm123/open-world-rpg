#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "TileContainer.h"
#include "TileMap.h"

class TileMapGenerator {
public:
    static TileMap::Tiles generate(sf::Vector2f pos, sf::Vector2i size);

private:
    static void
    assignContainer(const std::shared_ptr<TileContainer> & container, sf::Vector2i localCoords, TileMap::Tiles &tiles);

    static void
    fetchAndAssignTileContainer(sf::Vector2i localCoords, sf::Vector2f pos, TileMap::Tiles &tiles);
};





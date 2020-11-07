#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TileContainer.h"
#include "../Environments/Env.h"
#include "TileMap.h"


class TileMapGenerator {
public:
    static TileMap::Tiles generate(sf::Vector2f pos, sf::Vector2i size);

private:
    static void
    assignContainer(std::shared_ptr<TileContainer> container, sf::Vector2i localCoords, const TileMap::Tiles &tiles);

    static const TileContainer &
    fetchTileContainer(sf::Vector2i localCoords, sf::Vector2f pos, const TileMap::Tiles &tiles);
};





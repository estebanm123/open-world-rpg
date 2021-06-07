#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "TileMap.h"

class TileMapGenerator {
public:
	static TileMap::Tiles generate(sf::Vector2f pos);

private:
};

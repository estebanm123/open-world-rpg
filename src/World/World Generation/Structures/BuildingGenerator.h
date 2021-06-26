#pragma once

#include <memory>
#include <vector>

#include "../../Entities/Collidables/Props/Prop.h"

class BuildingGenerator {
public:
	// units are in tiles
	struct BuildingConfig {
		sf::Vector2f topLeft;
		int xLength = 1;
		int yLength = 1;
	};

	static constexpr int FLOOR_TILE_SIZEX = 16;
	static constexpr int FLOOR_TILE_SIZEY = FLOOR_TILE_SIZEX;

	std::vector<std::unique_ptr<Entity>> generateBuildings(const BuildingConfig & config);

protected:
	std::unique_ptr<Prop> generateFloorTile(sf::Vector2i localCoords, const BuildingConfig & config);
};



#include "BuildingGenerator.h"

#include <iostream>

std::vector<std::unique_ptr<Entity>> BuildingGenerator::generateBuildings(
 const BuildingGenerator::BuildingConfig& config) {
	std::vector<std::unique_ptr<Entity>> resultProps;

	for (auto y = 0; y < config.yLength; y++) {
		for (auto x = 0; x < config.xLength; x++) {
			auto floorTile = generateFloorTile({x, y}, config);
			resultProps.push_back(std::move(floorTile));
		}
	}

	generateVerticalWalls(resultProps, config);
	generateHorizontalWalls(resultProps, config);

	return resultProps;
}

std::unique_ptr<Prop> BuildingGenerator::generateFloorTile(
 sf::Vector2i localCoords,
 const BuildingGenerator::BuildingConfig& config) {
	auto tilePos = sf::Vector2f{static_cast<float>(localCoords.x * FLOOR_TILE_SIZEY),
								static_cast<float>(localCoords.y * FLOOR_TILE_SIZEX)} +
				   config.topLeft;

	auto PLACEHOLDER_SPRITE_SHEET = "Buildings/logs";
	return std::make_unique<Prop>(Prop::PropOptions{PLACEHOLDER_SPRITE_SHEET,
													{0, 0, 16, 16},
													tilePos,
													false,
													{0, 0},
													std::make_unique<CollisionPhysics>(),
													nullptr,
													nullptr,
													false,
													0});
}

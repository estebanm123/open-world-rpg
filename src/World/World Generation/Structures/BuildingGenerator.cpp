

#include "BuildingGenerator.h"

#include <iostream>

#include "../../Entities/Collidables/Collision Physics/BlockingPhysics.h"


void BuildingGenerator::generateRoom(std::vector<std::unique_ptr<Entity>>& resultEntities,
									 const BuildingGenerator::BuildingConfig& config) {
	for (auto y = 0; y < config.yLength; y++) {
		for (auto x = 0; x < config.xLength; x++) {
			auto floorTile = generateFloorTile({x, y}, config);
			resultEntities.push_back(std::move(floorTile));
		}
	}

	generateWalls(resultEntities, config);
}

std::vector<std::unique_ptr<Entity>> BuildingGenerator::generateBuildings(
 const BuildingGenerator::BuildingConfig& config) {
	std::vector<std::unique_ptr<Entity>> resultProps;

	generateRoom(resultProps, config);

	return resultProps;
}

void generateWallUtil(std::vector<std::unique_ptr<Entity>>& resultEntities,
					  sf::Vector2f pos,
					  float rotAngle) {
	auto PLACEHOLDER_SPRITE_SHEET = "Buildings/wall";
	resultEntities.push_back(std::make_unique<Prop>(Prop::PropOptions{
	 PLACEHOLDER_SPRITE_SHEET,
	 {0, 0, BuildingGenerator::WALL_TILE_SIZEX, BuildingGenerator::WALL_TILE_SIZEY},
	 pos,
	 false,
	 {0, 0},
	 std::make_unique<BlockingPhysics>(),
	 nullptr,
	 nullptr,
	 false,
	 rotAngle,
	 Entity::Altitude::MEDIUM}));
}

void generateHorizontalWall(float fixedLocalY,
							const BuildingGenerator::BuildingConfig& config,
							std::vector<std::unique_ptr<Entity>>& resultEntities) {
	auto y = fixedLocalY * BuildingGenerator::WALL_TILE_SIZEY + config.topLeft.y;
	float rotAngle = fixedLocalY == 0 ? 90 : 270;
	for (auto tileIndex = 0; tileIndex < config.xLength; tileIndex++) {
		auto x = tileIndex * BuildingGenerator::WALL_TILE_SIZEY + config.topLeft.x;
		generateWallUtil(resultEntities, sf::Vector2f{x, y}, rotAngle);
	}
}

void generateVerticalWall(float fixedLocalX,
						  const BuildingGenerator::BuildingConfig& config,
						  std::vector<std::unique_ptr<Entity>>& resultEntities) {
	auto x = fixedLocalX * BuildingGenerator::WALL_TILE_SIZEY + config.topLeft.x;
	auto rotAngle = fixedLocalX == 0 ? 0 : 180;
	for (auto tileIndex = 0; tileIndex < config.yLength; tileIndex++) {
		auto y = tileIndex * BuildingGenerator::WALL_TILE_SIZEY + config.topLeft.y;
		generateWallUtil(resultEntities, sf::Vector2f{x, y}, rotAngle);
	}
}

void BuildingGenerator::generateWalls(std::vector<std::unique_ptr<Entity>>& resultEntities,
									  const BuildingGenerator::BuildingConfig& config) {
	generateHorizontalWall(0, config, resultEntities);
	generateHorizontalWall(config.yLength - 1, config, resultEntities);
	generateVerticalWall(0, config, resultEntities);
	generateVerticalWall(config.xLength - 1, config, resultEntities);
}

std::unique_ptr<Prop> BuildingGenerator::generateFloorTile(
 sf::Vector2i localCoords,
 const BuildingGenerator::BuildingConfig& config) {
	auto tilePos = sf::Vector2f{static_cast<float>(localCoords.x * FLOOR_TILE_SIZEX),
								static_cast<float>(localCoords.y * FLOOR_TILE_SIZEY)} +
				   config.topLeft;

	auto PLACEHOLDER_SPRITE_SHEET = "Buildings/logs";
	return std::make_unique<Prop>(Prop::PropOptions{PLACEHOLDER_SPRITE_SHEET,
													{0, 0, FLOOR_TILE_SIZEX, FLOOR_TILE_SIZEY},
													tilePos,
													false,
													{0, 0},
													std::make_unique<CollisionPhysics>(),
													nullptr,
													nullptr,
													false,
													0,
													Entity::Altitude::LOW});
}

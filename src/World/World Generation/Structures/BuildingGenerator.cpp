

#include "BuildingGenerator.h"

#include <iostream>

#include "../../Entities/Collidables/Collision Physics/BlockingPhysics.h"
#include "../../Entities/Sprites/SpriteContainer.h"
#include "../../Entities/Sprites/SpriteReg.h"


void BuildingGenerator::generateRoom(std::vector<std::unique_ptr<Prop>>& resultEntities,
									 const BuildingGenerator::BuildingConfig& config) {
	for (auto y = 0; y < config.yLength; y++) {
		for (auto x = 0; x < config.xLength; x++) {
			auto floorTile = generateFloorTile({x, y}, config);
			//			resultEntities.push_back(std::move(floorTile));
		}
	}

	generateWalls(resultEntities, config);
}

std::vector<std::unique_ptr<Prop>> BuildingGenerator::generateBuildings(
 const BuildingGenerator::BuildingConfig& config) {
	std::vector<std::unique_ptr<Prop>> resultProps;

	generateRoom(resultProps, config);

	return resultProps;
}

std::unique_ptr<EntitySprite> initializeWallSprite(sf::Vector2f pos) {
	auto PLACEHOLDER_SPRITE_SHEET = "Buildings/wall";
	sf::IntRect PLACEHOLDER_DEFAULTFRAME = {0,
											0,
											BuildingGenerator::WALL_TILE_SIZEX,
											BuildingGenerator::WALL_TILE_SIZEY};
	auto size =
	 sf::Vector2f{BuildingGenerator::WALL_TILE_SIZEX, BuildingGenerator::WALL_TILE_SIZEY};
	return std::make_unique<SpriteReg>(SpriteReg::Config{PLACEHOLDER_SPRITE_SHEET,
														 pos,
														 size / 2.f,
														 nullptr,
														 PLACEHOLDER_DEFAULTFRAME});
}

void generateWallUtil(std::vector<std::unique_ptr<EntitySprite>> wallSprites,
					  std::vector<std::unique_ptr<Prop>>& resultEntities,
					  sf::Vector2f pos,
					  float rotAngle,
					  sf::Vector2f size) {
	auto sprite = std::make_unique<SpriteContainer>(std::move(wallSprites), true, pos);
	sprite->rotate(rotAngle);

	resultEntities.push_back(std::make_unique<Prop>(
	 Prop::PropOptions{"",
					   sf::IntRect{0, 0, static_cast<int>(size.x), static_cast<int>(size.y)},
					   pos,
					   false,
					   sf::Vector2i{0, 0},
					   std::make_unique<BlockingPhysics>(),
					   nullptr,
					   nullptr,
					   std::move(sprite),
					   false,
					   0,
					   Entity::Altitude::MEDIUM}));
}

void generateHorizontalWall(float fixedLocalY,
							const BuildingGenerator::BuildingConfig& config,
							std::vector<std::unique_ptr<Prop>>& resultEntities) {
	auto y = fixedLocalY * BuildingGenerator::WALL_TILE_SIZEY + config.topLeft.y;

	std::vector<std::unique_ptr<EntitySprite>> wallSprites;
	for (auto tileIndex = 0; tileIndex < config.xLength; tileIndex++) {
		auto x = tileIndex * BuildingGenerator::WALL_TILE_SIZEY + config.topLeft.x;
		wallSprites.push_back(initializeWallSprite(sf::Vector2f{x, y}));
	}
	float rotAngle = fixedLocalY == 0 ? 90 : 270;
	auto size =
	 sf::Vector2f{static_cast<float>(BuildingGenerator::WALL_TILE_SIZEY * config.xLength),
				  BuildingGenerator::WALL_TILE_SIZEX};
	auto centrePos =
	 sf::Vector2f{config.topLeft.x + (size.x - BuildingGenerator::WALL_TILE_SIZEY) / 2.f, y};
	generateWallUtil(std::move(wallSprites), resultEntities, centrePos, rotAngle, size);
}

void generateVerticalWall(float fixedLocalX,
						  const BuildingGenerator::BuildingConfig& config,
						  std::vector<std::unique_ptr<Prop>>& resultEntities) {
	auto x = fixedLocalX * BuildingGenerator::WALL_TILE_SIZEY + config.topLeft.x;

	std::vector<std::unique_ptr<EntitySprite>> wallSprites;
	for (auto tileIndex = 0; tileIndex < config.yLength; tileIndex++) {
		auto y = tileIndex * BuildingGenerator::WALL_TILE_SIZEY + config.topLeft.y;
		wallSprites.push_back(initializeWallSprite(sf::Vector2f{x, y}));
	}

	auto rotAngle = fixedLocalX == 0 ? 0 : 180;
	auto size =
	 sf::Vector2f{BuildingGenerator::WALL_TILE_SIZEX,
				  static_cast<float>(config.yLength * BuildingGenerator::WALL_TILE_SIZEY)};
	auto centrePos =
	 sf::Vector2f{x, config.topLeft.y + (size.y - BuildingGenerator::WALL_TILE_SIZEY) / 2.f};
	generateWallUtil(std::move(wallSprites), resultEntities, centrePos, rotAngle, size);
}

void BuildingGenerator::generateWalls(std::vector<std::unique_ptr<Prop>>& resultEntities,
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
													nullptr,
													false,
													0,
													Entity::Altitude::LOW});
}

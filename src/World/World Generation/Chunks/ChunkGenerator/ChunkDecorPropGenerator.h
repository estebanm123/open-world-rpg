#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include "../../Tiles/Tile.h"
#include "../../Tiles/TileMap.h"
#include "../Spatial Partitions/SpatialPartition.h"
#include "ChunkEnvBasedEntityGenerator.h"

class Tile;

class Prop;

class ChunkDecorPropGenerator : public ChunkEnvBasedEntityGenerator {
protected:
	bool isEntityValid(Entity *entity,
					   const TileMap &tiles,
					   TilesSeen &tilesSeen,
					   const sf::Vector2i &localCoords) override;

	std::unique_ptr<Entity> generateEntity(const CompleteEnv *curEnv, sf::Vector2f entityCoords) override;
};

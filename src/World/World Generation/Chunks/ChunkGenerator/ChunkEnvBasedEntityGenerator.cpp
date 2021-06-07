

#include "ChunkEnvBasedEntityGenerator.h"

#include "../../../../Util/Random/Hash.h"
#include "../../../Entities/Entity.h"
#include "../../Environments/CompleteEnv.h"
#include "../../Tiles/Tile.h"
#include "../Chunk.h"
#include "../Spatial Partitions/SpatialPartition.h"

sf::Vector2f generateEntityCoords(float entityGenLimit, int hashVal1, const sf::Vector2f &tileGlobalCoords) {
	using namespace worldConstants;
	auto hashVal2 = mixCoords(hashVal1, static_cast<int>(entityGenLimit));
	int limit = static_cast<int>(entityGenLimit);
	auto x = static_cast<float>(hashVal2 % TILE_SIZE_INT_X);
	auto y = static_cast<float>((limit * hashVal1) % TILE_SIZE_INT_Y);
	return {x + tileGlobalCoords.x, y + tileGlobalCoords.y};
}

void ChunkEnvBasedEntityGenerator::generateEntities(Chunk *chunk) {
	float currentEntityGenLimit = entityGenLimitInitial;
	TilesSeen tilesSeen = initializeTilesSeen();
	auto &tileMap = chunk->getTileMap();
	auto entitySpatialPartition = chunk->getSpatialPartition();

	for (int x = 0; x < TileMap::SIZE_X; x++) {
		for (int y = 0; y < TileMap::SIZE_Y; y++) {
			auto curTile = tileMap.getTile(x, y);
			auto curEnv = curTile->getEnvironment();
			auto tileCoordHash = hashTileCoords(*curTile) ^ static_cast<int>(currentEntityGenLimit);
			if (tileCoordHash > currentEntityGenLimit) {
				auto entityCoords =
					generateEntityCoords(currentEntityGenLimit, tileCoordHash, curTile->getTopLeftPos());
				auto entity = generateEntity(curEnv, entityCoords);
				if (!isEntityValid(entity.get(), tileMap, tilesSeen, {x, y})) {
					continue;
				}
				updateCurrentEntitiyLimitOnSuccess(currentEntityGenLimit);
				std::shared_ptr<Entity> entityPtr = std::move(entity);
				entitySpatialPartition->addNewEntity(entityPtr);
			} else {
				updateCurrentEntityLimitOnFailure(currentEntityGenLimit);
			}
		}
	}
}

ChunkEnvBasedEntityGenerator::TilesSeen ChunkEnvBasedEntityGenerator::initializeTilesSeen() {
	TilesSeen tilesSeen;
	for (auto &row : tilesSeen) {
		for (auto &marker : row) {
			marker = false;
		}
	}
	return tilesSeen;
}

void ChunkEnvBasedEntityGenerator::updateCurrentEntityLimitOnFailure(float &currentLimit) {
	currentLimit += entityGenLimitChange;
}

void ChunkEnvBasedEntityGenerator::updateCurrentEntitiyLimitOnSuccess(float &currentLimit) {
	if (currentLimit - entityGenLimitChange > 0) {
		currentLimit -= entityGenLimitChange;
	} else {
		currentLimit = 0;
	}
}

bool ChunkEnvBasedEntityGenerator::isEntityValid(Entity *entity,
												 const TileMap &tiles,
												 TilesSeen &tilesSeen,
												 const sf::Vector2i &localCoords) {
	if (!entity) return false;

	return !tiles.isEntityCrossingBounds(entity) &&
		   !isEntityOverlappingOthersAndMarkAsSeen(entity, localCoords, tilesSeen, tiles);
}

// Divisor used against entity's max length (width/height) - a larger value = higher chance of collisions but more
// natural results
constexpr auto ENTITY_COLLISION_LENIENCY_FACTOR = 3;

// Marks entity as seen
// Extra safe (a little inaccurate)
bool ChunkEnvBasedEntityGenerator::isEntityOverlappingOthersAndMarkAsSeen(
	Entity *entity,
	const sf::Vector2i &localCoords,
	ChunkEnvBasedEntityGenerator::TilesSeen &tilesSeen,
	const TileMap &tiles) {
	auto entitySize = entity->getSize();
	auto &entityPos = entity->getPosition();
	auto entityMaxLen = std::max(entitySize.y, entitySize.x) /
						ENTITY_COLLISION_LENIENCY_FACTOR;  // take max to be safe; entity could be rotated

	auto southEntityLim = tiles.convertGlobalToLocalCoords({entityPos.x, entityPos.y + entityMaxLen}).y;
	auto eastEntityLim = tiles.convertGlobalToLocalCoords({entityPos.x + entityMaxLen, entityPos.y}).x;
	auto northEntityLim = tiles.convertGlobalToLocalCoords({entityPos.x, entityPos.y - entityMaxLen}).y;
	auto westEntityLim = tiles.convertGlobalToLocalCoords({entityPos.x - entityMaxLen, entityPos.y}).x;

	bool isOverlapping = tilesSeen[localCoords.x][localCoords.y] || tilesSeen[localCoords.x][southEntityLim] ||
						 tilesSeen[localCoords.x][northEntityLim] || tilesSeen[westEntityLim][localCoords.y] ||
						 tilesSeen[eastEntityLim][localCoords.y];
	if (isOverlapping) return true;
	tilesSeen[localCoords.x][localCoords.y] = true;
	tilesSeen[localCoords.x][southEntityLim] = true;
	tilesSeen[localCoords.x][northEntityLim] = true;
	tilesSeen[westEntityLim][localCoords.y] = true;
	tilesSeen[eastEntityLim][localCoords.y] = true;
	return false;
}

int ChunkEnvBasedEntityGenerator::hashTileCoords(Tile &tile) {
	auto pos = tile.getTopLeftPos();
	auto tileCoordHash = hash2ValuesModSize(pos.x, pos.y, static_cast<int>(entityGenLimitMax));	 // never more than 1000
	return tileCoordHash;
}

ChunkEnvBasedEntityGenerator::ChunkEnvBasedEntityGenerator(const int entityGenLimitMax,
														   const int entityGenLimitChange,
														   const int entityGenLimitInitial)
	: entityGenLimitMax(entityGenLimitMax),
	  entityGenLimitChange(entityGenLimitChange),
	  entityGenLimitInitial(entityGenLimitInitial) {}

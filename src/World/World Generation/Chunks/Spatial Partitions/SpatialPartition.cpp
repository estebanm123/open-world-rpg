
#include "SpatialPartition.h"

#include <math.h>

using namespace worldConstants;

SpatialPartition::SpatialPartition(sf::Vector2f center) : topLeftCoords(center - worldConstants::CHUNK_SIZE / 2.f) {
	initSlots();
}

void SpatialPartition::setChunkNeighbors(Chunk::Neighbors *neighbors) { this->chunkNeighbors = neighbors; }

void SpatialPartition::initSlots() {
	for (auto row = 0; row < slots.size(); row++) {
		for (auto col = 0; col < slots[0].size(); col++) {
			slots[row][col] = std::make_unique<PartitionSlot>();
		}
	}
}

std::unordered_set<PartitionSlot *> SpatialPartition::getSlotsAroundEntity(sf::FloatRect rangeGlobal) {
	auto topLeftSlot = convertGlobalToLocalCoords({rangeGlobal.left, rangeGlobal.top});
	auto botRightSlot =
		convertGlobalToLocalCoords({rangeGlobal.left + rangeGlobal.width, rangeGlobal.top + rangeGlobal.height});
	topLeftSlot += sf::Vector2i{-1, -1};  // over-extend range to capture props that could be on the edge of a slot
	botRightSlot += sf::Vector2i{1, 1};
	return getSlotsInRange(topLeftSlot, botRightSlot);
}

void SpatialPartition::appendForeignSlotsInRange(std::unordered_set<PartitionSlot *> &resultSlots,
												 SpatialPartition *foreignSpatialPartition,
												 sf::Vector2i topLeftSlotCoords,
												 sf::Vector2i botRightSlotCoords) {
	if (foreignSpatialPartition == nullptr) return;
	auto foreignSlots = foreignSpatialPartition->getSlotsInRange(topLeftSlotCoords, botRightSlotCoords);
	for (auto slot : foreignSlots) {
		resultSlots.insert(slot);
	}
}

SpatialPartition *getForeignPartitionFrom(std::unique_ptr<Chunk> *chunkPtr) {
	if (chunkPtr == nullptr) return nullptr;
	if (*chunkPtr == nullptr) return nullptr;
	auto chunk = chunkPtr->get();
	return chunk == nullptr ? nullptr : chunk->getSpatialPartition();
}

std::unordered_set<PartitionSlot *> SpatialPartition::getSlotsInRange(sf::Vector2i topLeftLocalCoords,
																	  sf::Vector2i bottomRightLocalCoords) {
	std::unordered_set<PartitionSlot *> resultSlots;

	auto startRow = topLeftLocalCoords.y;
	auto startCol = topLeftLocalCoords.x;
	auto endRow = bottomRightLocalCoords.y;
	auto endCol = bottomRightLocalCoords.x;
	//    std::cout << startRow << "," << startCol << "," << endRow << "," << endCol << std::endl;
	if (startRow < 0) {	 // handle slots to the north of the partition
		auto foreignTopRow = SLOT_ROWS_PER_CHUNK + startRow;
		auto foreignBotRow = SLOT_ROWS_PER_CHUNK - 1;
		appendForeignSlotsInRange(resultSlots,
								  getForeignPartitionFrom(chunkNeighbors->north),
								  sf::Vector2i{startCol, foreignTopRow},
								  sf::Vector2i{endCol, foreignBotRow});
		startRow = 0;

		if (endRow < 0) {
			return resultSlots;	 // all relevant slots are north of us
		}
	} else if (startRow >= SLOT_ROWS_PER_CHUNK) {  // all relevant slots are south of us
		auto foreignTopRow = startRow - SLOT_ROWS_PER_CHUNK;
		auto foreignBotRow = endRow - SLOT_ROWS_PER_CHUNK;
		appendForeignSlotsInRange(resultSlots,
								  getForeignPartitionFrom(chunkNeighbors->south),
								  sf::Vector2i{startCol, foreignTopRow},
								  sf::Vector2i{endCol, foreignBotRow});
		return resultSlots;
	}
	if (endRow >= SLOT_ROWS_PER_CHUNK) {  // handle slots south of us
		auto foreignTopRow = 0;
		auto foreignBotRow = endRow - SLOT_ROWS_PER_CHUNK;	// make local coords relative to south partition
		appendForeignSlotsInRange(resultSlots,
								  getForeignPartitionFrom(chunkNeighbors->south),
								  sf::Vector2i{startCol, foreignTopRow},
								  sf::Vector2i{endCol, foreignBotRow});
		endRow = SLOT_ROWS_PER_CHUNK - 1;
	}
	// symmetrical cases except updated startRow/endRow
	if (startCol < 0) {
		auto foreignLeftCol = SLOT_COLS_PER_CHUNK + startCol;
		auto foreignRightCol = SLOT_COLS_PER_CHUNK - 1;
		appendForeignSlotsInRange(resultSlots,
								  getForeignPartitionFrom(chunkNeighbors->west),
								  sf::Vector2i{foreignLeftCol, startRow},
								  sf::Vector2i{foreignRightCol, endRow});
		startCol = 0;

		if (endCol < 0) {
			return resultSlots;
		}
	} else if (startCol >= SLOT_COLS_PER_CHUNK) {
		auto foreignLeftCol = startCol - SLOT_COLS_PER_CHUNK;
		auto foreignRightCol = endCol - SLOT_COLS_PER_CHUNK;
		appendForeignSlotsInRange(resultSlots,
								  getForeignPartitionFrom(chunkNeighbors->east),
								  sf::Vector2i{foreignLeftCol, startRow},
								  sf::Vector2i{foreignRightCol, endRow});
		return resultSlots;
	}
	if (endCol >= SLOT_COLS_PER_CHUNK) {
		auto foreignLeftCol = 0;
		auto foreignRightCol = endCol - SLOT_COLS_PER_CHUNK;
		appendForeignSlotsInRange(resultSlots,
								  getForeignPartitionFrom(chunkNeighbors->east),
								  sf::Vector2i{foreignLeftCol, startRow},
								  sf::Vector2i{foreignRightCol, endRow});
		endCol = SLOT_COLS_PER_CHUNK - 1;
	}

	for (auto row = startRow; row <= endRow; row++) {
		for (auto col = startCol; col <= endCol; col++) {
			resultSlots.insert(slots[row][col].get());
		}
	}
	return resultSlots;
}

bool SpatialPartition::activeZoneContainsSlot(int row, int col, const ActiveZone &activeZone) const {
	return activeZone.containsSlot({SLOT_WIDTH * col + topLeftCoords.x, SLOT_HEIGHT * row + topLeftCoords.y},
								   {SLOT_WIDTH, SLOT_HEIGHT});
}

void SpatialPartition::updateEntities(float dt, const ActiveZones &activeZones, Chunk *chunkOwner) {
	for (auto row = 0; row < slots.size(); row++) {
		for (auto col = 0; col < slots[0].size(); col++) {
			auto &slot = slots[row][col];
			if (activeZoneContainsSlot(row, col, activeZones.updateZone)) {
				slot->update(dt);
				slot->handleCollisions(this);
			}
		}
	}

	// At cost of spatial locality, ensure all collisions are resolved before handling tile collisions
	for (auto row = 0; row < slots.size(); row++) {
		for (auto col = 0; col < slots[0].size(); col++) {
			auto &slot = slots[row][col];
			if (activeZoneContainsSlot(row, col, activeZones.updateZone)) {
				slot->makeMoveablesInteractWithEnvironment(this, chunkOwner);
			}
		}
	}
}

void SpatialPartition::renderNonDecorEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones) {
	for (auto row = 0; row < slots.size(); row++) {
		for (auto col = 0; col < slots[0].size(); col++) {
			if (activeZoneContainsSlot(row, col, activeZones.renderZone)) {
				slots[row][col]->renderNonDecorEntities(renderer);
			}
		}
	}
}

void SpatialPartition::renderDecorEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones) {
	for (auto row = 0; row < slots.size(); row++) {
		for (auto col = 0; col < slots[0].size(); col++) {
			if (activeZoneContainsSlot(row, col, activeZones.renderZone)) {
				slots[row][col]->renderDecorEntities(renderer);
			}
		}
	}
}

void SpatialPartition::renderSurfaceEffects(sf::RenderTarget &renderer, const ActiveZones &activeZones) {
	for (auto row = 0; row < slots.size(); row++) {
		for (auto col = 0; col < slots[0].size(); col++) {
			if (activeZoneContainsSlot(row, col, activeZones.renderZone)) {
				slots[row][col]->renderSurfaceEffects(renderer);
			}
		}
	}
}

void SpatialPartition::addNewEntity(const std::shared_ptr<Entity> &entity) {
	auto localCoords = convertGlobalToLocalCoords(entity->getTopLeftPosition());
	if (localCoords.x < 0) {
		localCoords.x = 0;
	} else if (localCoords.x >= SLOT_COLS_PER_CHUNK) {
		localCoords.x = SLOT_COLS_PER_CHUNK - 1;
	}
	if (localCoords.y < 0) {
		localCoords.y = 0;
	} else if (localCoords.y >= SLOT_ROWS_PER_CHUNK) {
		localCoords.y = SLOT_ROWS_PER_CHUNK - 1;
	}

	slots[localCoords.y][localCoords.x]->addEntity(entity);
}

const int SpatialPartition::SLOT_WIDTH = static_cast<int>(worldConstants::CHUNK_SIZE.x) / SLOT_COLS_PER_CHUNK;
const int SpatialPartition::SLOT_HEIGHT = static_cast<int>(worldConstants::CHUNK_SIZE.y) / SLOT_ROWS_PER_CHUNK;

PartitionSlot *resolveForeignSlot(std::unique_ptr<Chunk> *chunk,
								  sf::Vector2f entityCenterPos,
								  sf::Vector2f entitySize) {
	auto foreignPartition = getForeignPartitionFrom(chunk);
	if (!foreignPartition) return nullptr;
	return foreignPartition->resolveSlotFromEntityGlobalCoords(entityCenterPos, entitySize);
}

PartitionSlot *SpatialPartition::resolveSlotFromEntityGlobalCoords(sf::Vector2f entityCenterPos,
																   sf::Vector2f entitySize) {
	auto entityTopLeft = entityCenterPos - sf::Vector2f{entitySize.x / 2, entitySize.y / 2};
	auto localCoords = convertGlobalToLocalCoords(entityTopLeft);
	//    std::cout << "local coords: " << localCoords.x << ", " << localCoords.y << std::endl;

	if (localCoords.x < 0) {
		return resolveForeignSlot(chunkNeighbors->west, entityCenterPos, entitySize);
	}
	if (localCoords.x >= SLOT_COLS_PER_CHUNK) {
		return resolveForeignSlot(chunkNeighbors->east, entityCenterPos, entitySize);
	}
	if (localCoords.y < 0) {
		return resolveForeignSlot(chunkNeighbors->north, entityCenterPos, entitySize);
	}
	if (localCoords.y >= SLOT_ROWS_PER_CHUNK) {
		return resolveForeignSlot(chunkNeighbors->south, entityCenterPos, entitySize);
	}

	return slots[localCoords.y][localCoords.x].get();
}

sf::Vector2i SpatialPartition::convertGlobalToLocalCoords(sf::Vector2f globalCoordsTopLeft) {
	auto relativeEntityGlobalCoords = (topLeftCoords - globalCoordsTopLeft);
	relativeEntityGlobalCoords = {std::abs(relativeEntityGlobalCoords.x), std::abs(relativeEntityGlobalCoords.y)};

	auto localCoords = sf::Vector2i{static_cast<int>(relativeEntityGlobalCoords.x) / SLOT_WIDTH,
									static_cast<int>(relativeEntityGlobalCoords.y) / SLOT_HEIGHT};

	// slot is in a foreign partition
	if (globalCoordsTopLeft.x < topLeftCoords.x) {
		localCoords.x = -localCoords.x - 1;
	}
	if (globalCoordsTopLeft.y < topLeftCoords.y) {
		localCoords.y = -localCoords.y - 1;
	}
	return localCoords;
}

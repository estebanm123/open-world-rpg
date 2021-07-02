#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <memory>

#include "../Chunk.h"
#include "PartitionSlot.h"

class ActiveZones;

using namespace worldConstants;

class SpatialPartition {
public:
	const static int SLOT_WIDTH;
	const static int SLOT_HEIGHT;

	SpatialPartition(sf::Vector2f center);

	void setChunkNeighbors(Chunk::Neighbors *neighbors);

	bool activeZoneContainsSlot(int row, int col, const ActiveZone &activeZone) const;

	void updateEntities(float dt, const ActiveZones &activeZones, Chunk *chunkOwner);

	void renderEntities(sf::RenderTarget &renderer,
						Entity::Altitude altitude,
						const ActiveZones &activeZones);

	void addNewEntity(const std::shared_ptr<Entity> &entity);

	template <class CollidableSubtype>
	void addCollidable(const std::shared_ptr<CollidableSubtype> &entity) {
		// todo - make this depend on a Collidable flag
		auto size = entity->getSize();
		auto pos = entity->getTopLeftPosition();
		auto slotsInRange = getSlotsAroundEntity(sf::FloatRect{pos.x, pos.y, size.x, size.y});
		auto REMOVE = slotsInRange.size();

		auto slotsIter = slotsInRange.begin();
		auto firstSlot = *slotsIter;

		firstSlot->addEntity(entity);
		std::for_each(++slotsIter, slotsInRange.end(), [entity](auto* slot) {
			slot->addCollisionOnlyEntity(entity);
		});
	}

	// ASSUMES entity is always moving to chunks that are loaded in
	PartitionSlot *resolveSlotFromEntityGlobalCoords(sf::Vector2f entityCenterPos,
													 sf::Vector2f entitySize);

	std::unordered_set<PartitionSlot *> getSlotsAroundEntity(sf::FloatRect rangeGlobal);

private:
	friend class ChunkDebug;

	void initSlots();

	std::unordered_set<PartitionSlot *> getSlotsInRange(sf::Vector2i topLeftLocalCoords,
														sf::Vector2i bottomRightLocalCoords);

	static void appendForeignSlotsInRange(std::unordered_set<PartitionSlot *> &resultSlots,
										  SpatialPartition *foreignSpatialPartition,
										  sf::Vector2i topLeftSlotCoords,
										  sf::Vector2i botRightSlotCoords);

	sf::Vector2i convertGlobalToLocalCoords(sf::Vector2f globalCoordsTopLeft);

	typedef std::array<std::array<std::unique_ptr<PartitionSlot>, SLOT_COLS_PER_CHUNK>,
					   SLOT_ROWS_PER_CHUNK>
	 Slots;
	Slots slots;
	sf::Vector2f topLeftCoords;
	Chunk::Neighbors *chunkNeighbors;
};
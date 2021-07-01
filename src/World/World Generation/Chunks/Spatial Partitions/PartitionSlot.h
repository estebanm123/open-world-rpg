#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <unordered_set>

#include "../../../Entities/Collidables/MoveableEntity.h"
#include "../../../Entities/Collidables/Organisms/Humanoid/Humanoid.h"
#include "../../../Entities/Collidables/Props/Prop.h"
#include "../Chunk.h"
#include "SlotEntities.h"

class SpatialPartition;

class PartitionSlot {
public:
	void update(float dt);

	void handleCollisions(SpatialPartition *slots);

	void makeMoveablesInteractWithEnvironment(SpatialPartition *spatialPartition, Chunk *chunk);

	void renderEntities(Entity::Altitude altitude, sf::RenderTarget & renderer);

	void handleExternalCollision(MoveableEntity *externalEntity);

	// Points to a Collidable in another slot; only collisions are handled through ptr
	template<class CollidableSubtype>
	void addCollisionOnlyEntity(const std::shared_ptr<CollidableSubtype> & collidable) {
		entityStorage.addCollidablePtr(collidable);
	}

	void addEntity(const std::shared_ptr<Entity> &entity);

	void removeEntity(const std::shared_ptr<Entity> &entity);

private:
	void handleCollisionsFor(MoveableEntity *moveable);

	void handleMoveableCollisions(SpatialPartition *spatialPartition);

	// Returns true if entity has moved to a different slot
	bool handleCollisionsWithOtherSlotEntities(MoveableEntity *moveable,
											   SpatialPartition *slots,
											   SlotEntities::MoveableIter &it);
	bool shouldSkipMoveablePair(MoveableEntity *a, MoveableEntity *b);

	SlotEntities entityStorage;
	std::unordered_set<std::string> moveablePairsSeenForCurUpdate;

	void handleSurfaceEffectGeneration(MoveableEntity *moveable, const CompleteEnv *env);


	friend class ChunkDebug;
};

#include <iostream>
#include <sstream>

#include "../../../Entities/Collidables/Hitbox/EntityCollisionHandler.h"
#include "../../../Entities/Surface Effects/SurfaceEffect.h"
#include "SpatialPartition.h"
#include "PartitionSlot.h"


void PartitionSlot::update(float dt) {
	for (auto &moveable : entityStorage.moveableEntities) {
		moveable->update(dt);
	}
	for (auto &effect : entityStorage.surfaceEffects) {
		effect->update(dt);
		if (effect->isReadyToBeRemoved()) {
			entityStorage.removeEntity(effect);
		}
	}
	for (auto &prop : entityStorage.mainProps) {
		prop->update(dt);
	}
}

void PartitionSlot::renderEntities(Entity::Altitude altitude, sf::RenderTarget &renderer) {
	auto mapIter = entityStorage.entities.entityMap.find(altitude);
	if (mapIter == entityStorage.entities.entityMap.end()) return;
	for (auto & entity : (*mapIter).second) {
		entity->renderBy(renderer);
	}
}

void PartitionSlot::handleMoveableCollisions(SpatialPartition *spatialPartition) {
	moveablePairsSeenForCurUpdate.clear();

	auto &moveables = entityStorage.moveableEntities;
	for (auto it = moveables.begin(); it != moveables.end();) {
		auto moveable = *it;

		handleCollisionsFor(moveable);
		if (!moveable->hasMoved()) {
			it++;
			continue;
		}
		bool entityMovedToAnotherSlot = handleCollisionsWithOtherSlotEntities(moveable, spatialPartition, it);

		if (!entityMovedToAnotherSlot) {
			it++;
		}
	}
}

void PartitionSlot::handleCollisions(SpatialPartition *slots) { handleMoveableCollisions(slots); }

void PartitionSlot::handleExternalCollision(MoveableEntity *externalEntity) { handleCollisionsFor(externalEntity); }

void PartitionSlot::addEntity(const std::shared_ptr<Entity> &entity) {
	entityStorage.addEntity(entity); }

void PartitionSlot::removeEntity(const std::shared_ptr<Entity> &entity) {
	entityStorage.removeEntity(entity); }

std::string moveableAddressesToStr(MoveableEntity *a, MoveableEntity *b) {
	std::ostringstream stream;
	if (a > b) {  // make sure they're always converted to string in the same order, so you always get the same
				  // resulting hash
		stream << a << b;
	} else {
		stream << b << a;
	}
	return stream.str();
}

bool PartitionSlot::shouldSkipMoveablePair(MoveableEntity *a, MoveableEntity *b) {
	if (a == b) return true;
	auto pairId = moveableAddressesToStr(a, b);
	return moveablePairsSeenForCurUpdate.find(pairId) != moveablePairsSeenForCurUpdate.end();
}

void PartitionSlot::handleCollisionsFor(MoveableEntity *moveable) {
	if (!moveable->hasMoved()) return;
	auto &moveableEntities = entityStorage.moveableEntities;
	for (auto otherMoveable : moveableEntities) {
		if (shouldSkipMoveablePair(moveable, otherMoveable)) continue;
		moveablePairsSeenForCurUpdate.insert(moveableAddressesToStr(moveable, otherMoveable));

		EntityCollisionHandler::handleCollision<MoveableEntity, MoveableEntity>(moveable, otherMoveable);
	}

	for (auto prop : entityStorage.mainProps) {
		EntityCollisionHandler::handleCollision<MoveableEntity, Prop>(moveable, prop);
	}
	for (auto prop : entityStorage.largePropPtrs) {
		EntityCollisionHandler::handleCollision<MoveableEntity, Prop>(moveable, prop.get());
	}
}

bool PartitionSlot::handleCollisionsWithOtherSlotEntities(MoveableEntity *moveable,
														  SpatialPartition *slots,
														  SlotEntities::MoveableIter &it) {
	auto moveablePos = moveable->getTopLeftPosition();
	auto moveableSize = moveable->getSize();
	auto slotsInRange =
		slots->getSlotsAroundEntity(sf::FloatRect{moveablePos.x, moveablePos.y, moveableSize.x, moveableSize.y});

	for (auto slot : slotsInRange) {
		if (slot == this) continue;
		slot->handleExternalCollision(moveable);
	}

	if (!moveable->hasMoved()) return false;
	auto currentSlot = slots->resolveSlotFromEntityGlobalCoords(moveable->getTopLeftPosition(), moveable->getSize());

	// check if moveable went out of bounds
	if (currentSlot == nullptr) {
		entityStorage.removeMoveable(moveable, it);
		return true;
	}

	// check if moveable was moved to another slot
	for (auto slot : slotsInRange) {
		if (currentSlot == slot) {
			auto entityPtr = entityStorage.removeMoveable(moveable, it);
			if (entityPtr != nullptr) {
				slot->addEntity(entityPtr);
			}
			return true;
		}
	}
	return false;
}

void PartitionSlot::makeMoveablesInteractWithEnvironment(SpatialPartition *spatialPartition, Chunk *chunk) {
	auto &tileMap = chunk->getTileMap();

	for (auto moveable : entityStorage.moveableEntities) {
		if (!moveable->hasMoved()) continue;

		auto moveablePos = moveable->getPosition();
		auto currentTile = tileMap.getTileFromGlobalCoords(moveablePos);
		auto env = currentTile->getEnvironment();
		auto envId = env->getId();
		if (!envId) {  // todo: placeholder; support border tiles
			handleSurfaceEffectGeneration(moveable, nullptr);
			return;
		}

		auto &unpassableEnvs = moveable->getUnpassableEnvs();
		if (unpassableEnvs.find(*env->getId()) != unpassableEnvs.end()) {
			moveable->handleUnpassableEnv(env);
		} else {
			handleSurfaceEffectGeneration(moveable, env);
		}
	}
}

void PartitionSlot::handleSurfaceEffectGeneration(MoveableEntity *moveable, const CompleteEnv *env) {
	auto moveableSurfaceEffectGenerator = moveable->getSurfaceEffectGenerator();
	if (moveableSurfaceEffectGenerator) {
		auto newSurfaceEffect =
			moveableSurfaceEffectGenerator->generateSurfaceEffect(moveable, env ? env->getId() : nullptr);
		if (newSurfaceEffect) {
			entityStorage.addEntity(std::move(newSurfaceEffect));
		}
	}

	if (!env) return;
	auto envSurfaceEffectGenerators = env->getSurfaceEffectGenerators();
	if (!envSurfaceEffectGenerators) return;
	for (auto &surfaceEffectGenerator : *envSurfaceEffectGenerators) {
		auto newSurfaceEffect = surfaceEffectGenerator->generateSurfaceEffect(moveable, nullptr);
		if (newSurfaceEffect) {
			entityStorage.addEntity(std::move(newSurfaceEffect));
		}
	}
}

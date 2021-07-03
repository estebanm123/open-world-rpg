

#include "BlockingPhysics.h"

#include <iostream>
#include "../Hitbox/EntityCollisionHandler.h"
#include "../MoveableEntity.h"

BlockingPhysics::BlockingPhysics(bool collisionAnalysisEnabledMoveables,
								 bool collisionAnalysisEnabledProps)
	: CollisionPhysics(collisionAnalysisEnabledMoveables, collisionAnalysisEnabledProps) {}

bool isXDistLarger(const sf::Vector2f &vec) { return abs(vec.x) > abs(vec.y); }

bool areVectorsInASharedQuadrant(const sf::Vector2f &a, const sf::Vector2f &b) {
	return (a.x > 0 && b.x > 0) || (a.x < 0 && b.x < 0) || (a.y > 0 && b.y > 0) ||
		   (a.y < 0 && b.y < 0);
}

static Random<> random{1};

void BlockingPhysics::applyPhysics(CollidableEntity *receivingEntity, MoveableEntity *other) {
	const auto savedPos = other->getPosition();
	const auto savedMoveOffset = other->getLastMoveOffset();

	other->revertLastMove(true, false);
	if (EntityCollisionHandler::areEntitiesColliding(receivingEntity, other)) {
		other->setPosition(savedPos);
		other->setLastMoveOffset(savedMoveOffset);
		other->revertLastMove(false, true);
		if (EntityCollisionHandler::areEntitiesColliding(receivingEntity, other)) {
			other->revertLastMove(true, true);
		}
	}

	//	// check to see if each vec shares a common quadrant - where origin is vecFromOtherEntity
	//	if (areVectorsInASharedQuadrant(vecFromOtherToEntity, lastMoveOffset)) {
	//		// if other is going in the dir of entity
	//		auto isXLarger = isXDistLarger(vecFromOtherToEntity);
	//		other->revertLastMove(isXLarger, !isXLarger);
	//		// what about the case where x + y are equal (ie. we're moving in a pure diagonal way)
	//	}

	CollisionPhysics::applyPhysics(receivingEntity, other);
}

bool BlockingPhysics::isBlocking() const { return true; }

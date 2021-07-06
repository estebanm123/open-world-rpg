

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
	const auto curPos = other->getPosition();
	const auto savedMoveOffset = other->getLastMoveOffset();
	const auto prevPos = curPos - savedMoveOffset;
	other->revertLastMove(true, true);

	// get each side of receiver
	// find intersecting side with MoveDir
	//
	//

//	other->setPosition({prevPos.x, curPos.y});
//	if (EntityCollisionHandler::areEntitiesColliding(receivingEntity, other)) {
//		other->setPosition({curPos.x, prevPos.y});
//		if (EntityCollisionHandler::areEntitiesColliding(receivingEntity, other)) {
//			other->setPosition(prevPos);
//		}
//	}

	//	// check to see if each vec shares a common quadrant - where origin is vecFromOtherEntity
	//	if (areVectorsInASharedQuadrant(vecFromOtherToEntity, lastMoveOffset)) {
	//		// if other is going in the dir of entity
	//		auto isXLarger = isXDistLarger(vecFromOtherToEntity);
//			other->revertLastMove(isXLarger, !isXLarger);
	//		// what about the case where x + y are equal (ie. we're moving in a pure diagonal way)
	//	}

	CollisionPhysics::applyPhysics(receivingEntity, other);
}

bool BlockingPhysics::isBlocking() const { return true; }

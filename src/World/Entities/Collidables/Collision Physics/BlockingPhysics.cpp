

#include "BlockingPhysics.h"

#include <iostream>

#include "../../../../Util/Shapes/ConvexShapeExtra.h"
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

void BlockingPhysics::applyPhysics(CollisionInfo<MoveableEntity> &collisionInfo) {
	const auto other = collisionInfo.otherEntity;
	const auto otherPos = collisionInfo.otherEntity->getPosition();
//	const auto savedMoveOffset = other->getLastMoveOffset();
//	const auto prevPos = otherPos - savedMoveOffset;
//	other->revertLastMove(true, true);

	// assumes hitbox is a quad
	const auto otherHitbox = collisionInfo.otherEntityHitbox;

	const auto moveDir = other->getMoveDirection();
	if (moveDir.x == 0 && moveDir.y == 0) return;

	const auto sides = ConvexShapeExtra::getGlobalEdges(otherHitbox->getBounds());
	for (auto edge : sides) {
		// just find edge with shortest dist to receiver center
	}


	// get each side of receiver
	// find intersecting side with MoveDir, if there is none return immediately
	// based on side's pos to others, check if MoveDir's angle is within proper range for that side


	//	other->setPosition({prevPos.x, otherPos.y});
	//	if (EntityCollisionHandler::areEntitiesColliding(receivingEntity, other)) {
	//		other->setPosition({otherPos.x, prevPos.y});
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

	CollisionPhysics::applyPhysics(collisionInfo);
}

bool BlockingPhysics::isBlocking() const { return true; }

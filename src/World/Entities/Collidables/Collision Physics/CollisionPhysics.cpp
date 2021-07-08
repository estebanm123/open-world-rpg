

#include "CollisionPhysics.h"

#include "../CollidableEntity.h"
#include "../MoveableEntity.h"
#include "../Props/Prop.h"

void CollisionPhysics::applyPhysics(CollisionInfo<MoveableEntity> &collisionInfo) {
	auto owner = collisionInfo.receivingEntity;
	auto movingEntity = collisionInfo.otherEntity;
	if (collisionAnalysisIsEnabledMoveables) {
		owner->analyzeCollision(movingEntity);
	}
}

void CollisionPhysics::applyPhysics(CollisionInfo<Prop> &collisionInfo) {
	auto owner = collisionInfo.receivingEntity;
	auto prop = collisionInfo.otherEntity;
	if (collisionAnalysisIsEnabledProps) {
		owner->analyzeCollision(prop);
	}
}

bool CollisionPhysics::isBlocking() const { return false; }
CollisionPhysics::CollisionPhysics(bool collisionAnalysisIsEnabledMoveables,
								   bool collisionAnalysisIsEnabledProps)
	: collisionAnalysisIsEnabledMoveables(collisionAnalysisIsEnabledMoveables),
	  collisionAnalysisIsEnabledProps(collisionAnalysisIsEnabledProps) {}

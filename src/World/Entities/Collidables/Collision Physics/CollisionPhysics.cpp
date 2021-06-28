

#include "CollisionPhysics.h"

#include "../CollidableEntity.h"
#include "../MoveableEntity.h"
#include "../Props/Prop.h"

void CollisionPhysics::applyPhysics(CollidableEntity *owner, MoveableEntity *movingEntity) {
	if (collisionAnalysisIsEnabledMoveables) {
		owner->analyzeCollision(movingEntity);
	}
}

void CollisionPhysics::applyPhysics(CollidableEntity *owner, Prop *prop) {
	if (collisionAnalysisIsEnabledProps) {
		owner->analyzeCollision(prop);
	}
}

bool CollisionPhysics::isBlocking() const { return false; }
CollisionPhysics::CollisionPhysics(bool collisionAnalysisIsEnabledMoveables,
								   bool collisionAnalysisIsEnabledProps)
	: collisionAnalysisIsEnabledMoveables(collisionAnalysisIsEnabledMoveables),
	  collisionAnalysisIsEnabledProps(collisionAnalysisIsEnabledProps) {}

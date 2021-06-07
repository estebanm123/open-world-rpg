#pragma once

#include "CollisionPhysics.h"

class ViewConePhysics : public CollisionPhysics {
	void applyPhysics(CollidableEntity *owner, MoveableEntity *movingEntity) override;
	void applyPhysics(CollidableEntity *owner, Prop *prop) override;
};

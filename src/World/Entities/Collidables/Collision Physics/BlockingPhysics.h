#pragma once

#include "CollisionPhysics.h"

class BlockingPhysics : public CollisionPhysics {
public:
	BlockingPhysics();

	bool isBlocking() const override;

	void applyPhysics(CollidableEntity *receivingEntity, MoveableEntity *other) override;
};

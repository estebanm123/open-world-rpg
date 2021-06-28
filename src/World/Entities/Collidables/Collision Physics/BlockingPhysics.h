#pragma once

#include "CollisionPhysics.h"

class BlockingPhysics : public CollisionPhysics {
public:
	BlockingPhysics(bool collisionAnalysisEnabledMoveables = false,
					bool collisionAnalysisEnabledProps = false);

	bool isBlocking() const override;

	void applyPhysics(CollidableEntity *receivingEntity, MoveableEntity *other) override;
private:
	bool collisionAnalysisEnabled;
};

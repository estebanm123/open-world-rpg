#pragma once

#include "CollisionPhysics.h"

class BlockingPhysics : public CollisionPhysics {
public:
    BlockingPhysics();

    void applyCollisionPhysics(CollidableEntity * receivingEntity, MoveableEntity *other) override;
};





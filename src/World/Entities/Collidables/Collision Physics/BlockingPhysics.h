#pragma once

#include "CollisionPhysics.h"

class BlockingPhysics : public CollisionPhysics {
public:
    BlockingPhysics();

    void applyPhysics(CollidableEntity * receivingEntity, MoveableEntity *other) override;
    void applyPhysics(CollidableEntity * receivingEntity, Prop *other) override;
};





#pragma once

#include "CollisionPhysics.h"

class BlockingPhysics : public CollisionPhysics {
public:
    explicit BlockingPhysics(CollidableEntity *entity);

    BlockingPhysics();

    void applyCollisionPhysics(MoveableEntity *other) override;

private:
};





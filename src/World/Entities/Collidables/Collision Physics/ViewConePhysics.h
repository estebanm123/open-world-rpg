#pragma once


#include "CollisionPhysics.h"

class ViewConePhysics : public CollisionPhysics {
    virtual void applyPhysics(CollidableEntity * owner, MoveableEntity *movingEntity);
    virtual void applyPhysics(CollidableEntity * owner, Prop *prop);
};





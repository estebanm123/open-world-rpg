

#include "ViewConePhysics.h"
#include "../MoveableEntity.h"
#include "../Props/Prop.h"

void ViewConePhysics::applyPhysics(CollidableEntity *owner, MoveableEntity *movingEntity) {
    owner->analyzeCollision(movingEntity);
}

void ViewConePhysics::applyPhysics(CollidableEntity *owner, Prop *prop) {
    owner->analyzeCollision(prop);
}

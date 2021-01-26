

#include "CollisionPhysics.h"

void CollisionPhysics::applyCollisionPhysics(MoveableEntity *other) {}

CollisionPhysics::CollisionPhysics(CollidableEntity *entity) : entity(entity) {}

CollisionPhysics::CollisionPhysics() : entity(nullptr) {}

void CollisionPhysics::setEntity(CollidableEntity *newEntity) {
    entity = newEntity;
}

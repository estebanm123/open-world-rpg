

#include "OrganismEntity.h"

OrganismEntity::OrganismEntity(const Hitbox &hitbox)
        : MoveableEntity(hitbox, std::make_unique<CollisionPhysics>()) {
}
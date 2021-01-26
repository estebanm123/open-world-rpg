

#include "OrganismEntity.h"
#include "../Collision Physics/BlockingPhysics.h"

OrganismEntity::OrganismEntity(const Hitbox &hitbox)
        : MoveableEntity(hitbox, std::make_unique<CollisionPhysics>(this)) {
}
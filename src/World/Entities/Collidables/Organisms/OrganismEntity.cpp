

#include "OrganismEntity.h"
#include "../Hitbox/Hitbox.h"

OrganismEntity::OrganismEntity(std::unique_ptr<Hitbox> hitbox)
        : MoveableEntity(std::move(hitbox)) {
}
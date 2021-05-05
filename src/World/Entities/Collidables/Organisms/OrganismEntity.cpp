

#include "OrganismEntity.h"
#include "../Hitbox/Hitbox.h"

OrganismEntity::OrganismEntity(Config hitboxes)
        : MoveableEntity(std::move(hitboxes)) {
}


#include "OrganismEntity.h"

OrganismEntity::OrganismEntity(Config hitboxes, float initialSpeed)
	: MoveableEntity(std::move(hitboxes), initialSpeed) {}
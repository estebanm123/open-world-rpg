

#include "OrganismEntity.h"

OrganismEntity::OrganismEntity(Config hitboxes, float initialSpeed, FoodChainLevel foodChainLevel)
	: MoveableEntity(std::move(hitboxes), initialSpeed) {}
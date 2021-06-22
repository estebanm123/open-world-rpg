

#include "OrganismEntity.h"

OrganismEntity::OrganismEntity(Config hitboxes, float initialSpeed, FoodChainLevel foodChainLevel)
	: MoveableEntity(std::move(hitboxes), initialSpeed),
	  foodChainLevel(foodChainLevel) {}

OrganismEntity::FoodChainLevel OrganismEntity::getFoodChainLevel() const { return foodChainLevel; }

void OrganismEntity::setFoodChainLevel(OrganismEntity::FoodChainLevel level) {
	foodChainLevel = level;
}

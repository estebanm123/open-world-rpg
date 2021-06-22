#pragma once

#include "../MoveableEntity.h"

class OrganismEntity : public MoveableEntity {
public:
	enum FoodChainLevel { LOWEST = 0, LOW = 1, MEDIUM = 1, HIGH = 2, HIGHEST = 3 };

	explicit OrganismEntity(Config hitboxes, float initialSpeed, FoodChainLevel foodChainLevel);

	~OrganismEntity() override = default;

protected:
};

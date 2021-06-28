#pragma once

#include "../MoveableEntity.h"

class OrganismEntity : public MoveableEntity {
public:
	enum FoodChainLevel {
		LOWEST = -2,
		VERY_LOW = -1,
		LOW = 0,
		MEDIUM = 1,
		HIGH = 2,
		VERY_HIGH = 3,
		HIGHEST = 4,
		NOT_APPLICABLE = 10
	};

	explicit OrganismEntity(Config hitboxes,
							float initialSpeed,
							FoodChainLevel foodChainLevel = NOT_APPLICABLE);

	~OrganismEntity() override = default;

	FoodChainLevel getFoodChainLevel() const;

	void setFoodChainLevel(FoodChainLevel level);

private:
	FoodChainLevel foodChainLevel;
};

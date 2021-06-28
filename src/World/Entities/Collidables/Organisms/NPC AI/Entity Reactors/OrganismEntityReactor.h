#pragma once

#include "../Activities/Single Activities/Flee.h"
#include "../Activities/Single Activities/Chase.h"
#include "EntityReactor.h"

template <class OrganismOwner, class OtherOrganism>
class OrganismEntityReactor : public EntityReactor<OrganismOwner, OtherOrganism> {
public:
	void analyzeCollision(OrganismOwner *receivingEntity,
						  NpcAi<OrganismOwner> *ai,
						  OtherOrganism *otherEntity) override {
		auto ownerFoodChainLvl = receivingEntity->getFoodChainLevel();
		auto otherFoodChainLvl = otherEntity->getFoodChainLevel();

		if (ownerFoodChainLvl == otherFoodChainLvl ||
			ownerFoodChainLvl == OrganismEntity::FoodChainLevel::NOT_APPLICABLE ||
			otherFoodChainLvl == OrganismEntity::FoodChainLevel::NOT_APPLICABLE) {
			EntityReactor<OrganismOwner, OtherOrganism>::handleBlockingEntity(receivingEntity,
																			  ai,
																			  otherEntity);
		} else if (ownerFoodChainLvl < otherFoodChainLvl) {
			ai->getActivitySchedule()->add(
			 std::make_unique<Flee<OrganismOwner, OtherOrganism>>(otherEntity));
		} else {
//			ai->getActivitySchedule()->add(
//			 std::make_unique<Chase<OrganismOwner, OtherOrganism>>(otherEntity));
		}
	}
};

#pragma once

#include "../../Humanoid/Humanoid.h"
#include "EntityReactor.h"

template <class OrganismNpc>
class HumanoidReactor : public EntityReactor<OrganismNpc, Humanoid> {
public:
	void analyzeCollision(OrganismNpc *receivingEntity, NpcAi<OrganismNpc> *ai, Humanoid *otherEntity) override {
		this->handleBlockingEntity(receivingEntity, ai, otherEntity);
	}
};

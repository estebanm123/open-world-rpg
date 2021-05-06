#pragma once


#include "EntityReactor.h"
#include "../../Beast/Beast.h"

template <class OrganismNpc>
class BeastReactor : public EntityReactor<OrganismNpc, Beast> {
public:
    void analyzeCollision(OrganismNpc *receivingEntity, NpcAi<OrganismNpc> * ai, Beast *otherEntity) override {
        this->handleBlockingEntity(receivingEntity, ai, otherEntity);
    }
};





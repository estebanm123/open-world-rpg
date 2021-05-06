#pragma once


#include "../../../Props/Prop.h"
#include "EntityReactor.h"

template<class OrganismNpc>
class PropReactor : public EntityReactor<OrganismNpc, Prop> {
public:

    void analyzeCollision(OrganismNpc *receivingEntity, NpcAi<OrganismNpc> * ai, Prop *otherEntity) override {
        this->handleBlockingEntity(receivingEntity, ai, otherEntity);
    }

protected:
    bool isEntityBlockingPath(OrganismNpc *receivingEntity, NpcAi<OrganismNpc>* ai, Prop *otherEntity) override {
        return otherEntity->isPropBlocking() &&
               EntityReactor<OrganismNpc, Prop>::isEntityBlockingPath(receivingEntity, ai, otherEntity);
    }
};





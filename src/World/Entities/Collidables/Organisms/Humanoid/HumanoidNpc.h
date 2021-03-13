#pragma once


#include "../NPC AI/NpcAi.h"
#include "Humanoid.h"

class HumanoidNpc : public Humanoid {
    void accept(EntityVisitor * visitor) override;

private:
    NpcAi<Humanoid> * ai;
};





#pragma once


#include "../NPC AI/NpcAi.h"
#include "Humanoid.h"

class HumanoidNpc : public Humanoid {
public:
    HumanoidNpc(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
                const std::string &spriteSheetHead, NpcAi<HumanoidNpc> *ai);

private:

    void accept(EntityVisitor *visitor) override;

private:
    NpcAi<HumanoidNpc> *ai;
};





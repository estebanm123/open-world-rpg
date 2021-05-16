#pragma once


#include "../NPC AI/NpcAi.h"
#include "Humanoid.h"

class HumanoidNpc : public Humanoid {
public:
    HumanoidNpc(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
                const std::string &spriteSheetHead, NpcAi<HumanoidNpc> ai, float initialSpeed);

    void update(float dt) override;

    void analyzeCollision(CollidableEntity *otherEntity) override;
private:
    void accept(EntityVisitor *visitor) override;

private:
    std::unique_ptr<NpcAi<HumanoidNpc>> ai;
};



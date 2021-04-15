

#include "../NPC AI/NpcAi.h"
#include "HumanoidNpc.h"

void HumanoidNpc::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

HumanoidNpc::HumanoidNpc(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
                         const std::string &spriteSheetHead, NpcAi<HumanoidNpc> *ai) : Humanoid(globalPosition,
                                                                                                spriteSheetBody,
                                                                                                spriteSheetHead),
                                                                                       ai(ai) {
    ai->init(this);
}

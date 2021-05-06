

#include "../NPC AI/NpcAi.h"
#include "HumanoidNpc.h"

void HumanoidNpc::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

HumanoidNpc::HumanoidNpc(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
                         const std::string &spriteSheetHead, NpcAi<HumanoidNpc> ai):
                         Humanoid(globalPosition, spriteSheetBody, spriteSheetHead),
                         ai(std::make_unique<NpcAi<HumanoidNpc>>(std::move(ai))) {

    this->ai->init(this);
}

void HumanoidNpc::update(float dt) {
    MoveableEntity::update(dt);
    ai->update(dt);
}

sf::Vector2f HumanoidNpc::getMoveOffset() {
    auto offset = MoveableEntity::getMoveOffset();
    return offset * static_cast<float>(.1);
}

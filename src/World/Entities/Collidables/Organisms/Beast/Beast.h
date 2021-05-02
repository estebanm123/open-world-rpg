#pragma once

#include "../OrganismEntity.h"
#include "../NPC AI/NpcAi.h"
#include "../../../Sprites/ShadowedSpriteReg.h"

class Beast : public OrganismEntity {
public:
    Beast(std::unique_ptr<Hitbox> hitbox, NpcAi<Beast> ai, ShadowedSpriteReg sprite);

    void accept(EntityVisitor *visitor) override;

    void update(float dt) override;

protected:
    EntitySprite &getSprite() override;

    sf::Vector2f getMoveOffset() override;

private:
    NpcAi<Beast> ai;
    ShadowedSpriteReg sprite;
};





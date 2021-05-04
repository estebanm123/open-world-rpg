#pragma once

#include "../OrganismEntity.h"
#include "../NPC AI/NpcAi.h"
#include "../../../Sprites/ShadowedSpriteReg.h"
#include "../../../Sprites/SpriteReg.h"

class Beast : public OrganismEntity {
public:
    Beast(std::unique_ptr<Hitbox> hitbox, NpcAi<Beast> ai, std::unique_ptr<SpriteReg> sprite);

    void accept(EntityVisitor *visitor) override;

    void update(float dt) override;

protected:
    EntitySprite &getSprite() override;

    sf::Vector2f getMoveOffset() override;

private:
    NpcAi<Beast> ai;
    std::unique_ptr<SpriteReg> sprite;
};





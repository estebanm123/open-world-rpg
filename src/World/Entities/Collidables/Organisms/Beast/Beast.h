#pragma once

#include "../OrganismEntity.h"
#include "../NPC AI/NpcAi.h"
#include "../../../Sprites/SpriteReg.h"

class Beast : public OrganismEntity {
public:
    Beast(std::unique_ptr<Hitbox> hitbox, NpcAi<Beast> ai, SpriteReg sprite);

    void accept(EntityVisitor *visitor) override;

    void update(float dt) override;

protected:
    EntitySprite &getSprite() override;

private:
    NpcAi<Beast> ai;
    SpriteReg sprite;
};





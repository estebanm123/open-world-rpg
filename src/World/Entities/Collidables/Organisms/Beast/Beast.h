#pragma once

#include "../OrganismEntity.h"
#include "../../../Sprites/ShadowedSpriteReg.h"
#include "../../../Sprites/SpriteReg.h"

template<class T>
class NpcAi;

class Beast : public OrganismEntity {
public:
    Beast(Config hitboxes, NpcAi<Beast> ai, std::unique_ptr<SpriteReg> sprite);

    void accept(EntityVisitor *visitor) override;

    void update(float dt) override;

protected:
    EntitySprite &getSprite() override;

    sf::Vector2f getMoveOffset() override;

private:
    std::unique_ptr<NpcAi<Beast>> ai;
    std::unique_ptr<SpriteReg> sprite;
};





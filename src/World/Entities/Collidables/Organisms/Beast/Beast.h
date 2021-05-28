#pragma once

#include "../OrganismEntity.h"
#include "../../../Sprites/ShadowedSpriteReg.h"
#include "../../../Sprites/SpriteReg.h"

template<class T>
class NpcAi;

class Beast : public OrganismEntity {
public:
    Beast(Config hitboxes, NpcAi<Beast> ai, std::unique_ptr<SpriteReg> sprite, float initialSpeed);

    void accept(EntityVisitor *visitor) override;

    void update(float dt) override;

    void analyzeCollision(CollidableEntity *otherEntity) override;

    void handleUnpassableEnv(const CompleteEnv *env) override;

protected:
    EntitySprite &getSprite() override;

    sf::Vector2f getMoveOffset() override;

private:
    std::unique_ptr<NpcAi<Beast>> ai;
    std::unique_ptr<SpriteReg> sprite;
};





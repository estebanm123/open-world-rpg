#pragma once

#include "../../Entity.h"
#include "../../RegSprite.h"
#include "../CollidableEntity.h"
#include "../../../../Animation/AnimationPlayer.h"

class Prop : public CollidableEntity {
public:
    Prop(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &size,
         std::unique_ptr<CollisionPhysics> collisionPhysics,
         std::unique_ptr<AnimationPlayer> animPlayer, const sf::IntRect &defaultFrame);

    void update(float dt) override;

protected:
    EntitySprite &getSprite() override;

    RegSprite sprite;
    std::unique_ptr<AnimationPlayer> animPlayer;
    bool hasDefaultAnim;
};





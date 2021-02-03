#pragma once

#include "../../Entity.h"
#include "../../RegSprite.h"
#include "../CollidableEntity.h"
#include "../../../../Animation/AnimationPlayer.h"
#include "../../../../Util/Random/Hash.h"
#include "../Collision Physics/BlockingPhysics.h"

class Prop : public CollidableEntity {
public:
    struct PropOptions {
        static constexpr auto PRIME = 73924247.f;
        explicit PropOptions(const sf::Vector2f &pos) : pos(pos) {};

        std::unique_ptr<AnimationPlayer> animPlayer = std::make_unique<AnimationPlayer>();
        std::unique_ptr<CollisionPhysics> collisionPhysics = std::make_unique<BlockingPhysics>();
        sf::Vector2f pos;
        float rotationAngle = static_cast<float>(hash2ValuesModSize(pos.x, pos.y * PRIME, 360));
    };

    Prop(const std::string &spriteSheet, const sf::Vector2f &size, const sf::IntRect &defaultFrame, PropOptions config);

    void update(float dt) override;

protected:
    EntitySprite &getSprite() override;

    RegSprite sprite;
    std::unique_ptr<AnimationPlayer> animPlayer;
    bool hasDefaultAnim;
};





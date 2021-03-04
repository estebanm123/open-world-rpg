#pragma once

#include "../../Entity.h"
#include "../../Sprites/SpriteReg.h"
#include "../CollidableEntity.h"
#include "../../../../Animation/AnimationPlayer.h"
#include "../../../../Util/Random/Hash.h"
#include "../Collision Physics/BlockingPhysics.h"
#include "../Hitbox/Hitbox.h"

class Prop : public CollidableEntity {
public:
    struct PropOptions {
        static constexpr auto PRIME = 73924247.f;

        explicit PropOptions(const sf::Vector2f &pos,
                             bool hasShadow = false,
                             std::unique_ptr<CollisionPhysics> collisionPhysics = std::make_unique<CollisionPhysics>(),
                             std::unique_ptr<AnimationPlayer> animPlayer = nullptr)
                : hasShadow(hasShadow), pos(pos), collisionPhysics(std::move(collisionPhysics)),
                  animPlayer(std::move(animPlayer)) {
        };
        std::unique_ptr<CollisionPhysics> collisionPhysics;
        std::unique_ptr<AnimationPlayer> animPlayer;
        sf::Vector2f pos;
        bool hasShadow;
        float rotationAngle = static_cast<float>(hash2ValuesModSize(pos.x, pos.y * PRIME, 360));
    };

    Prop(const std::string &spriteSheet, const sf::Vector2f &size, const sf::IntRect &defaultFrame, PropOptions config);

    void update(float dt) override;

protected:
    EntitySprite &getSprite() override;

    std::unique_ptr<EntitySprite> sprite;
    bool hasDefaultAnim;
};


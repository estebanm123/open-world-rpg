#pragma once

#include <utility>

#include "../../Sprites/SpriteReg.h"
#include "../CollidableEntity.h"
#include "../../../../Animation/AnimationPlayer.h"
#include "../../../../Util/Random/Hash.h"

class Prop : public CollidableEntity {
public:
    struct PropOptions {
        static constexpr auto PRIME = 73924247.f;

        explicit PropOptions(std::string spriteSheet, const sf::IntRect &defaultFrame,
                             const sf::Vector2f &pos, bool hasShadow = false, sf::Vector2i hitboxSizeOffset = {0, 0},
                             std::unique_ptr<CollisionPhysics> collisionPhysics = std::make_unique<CollisionPhysics>(),
                             std::unique_ptr<AnimationPlayer> animPlayer = nullptr)
                : hasShadow(hasShadow), spriteSheet(std::move(spriteSheet)), defaultFrame(defaultFrame),
                  size(hitboxSizeOffset + sf::Vector2i{defaultFrame.width, defaultFrame.height}), pos(pos),
                  collisionPhysics(std::move(collisionPhysics)),
                  animPlayer(std::move(animPlayer)) {
        };
        std::string spriteSheet;
        sf::IntRect defaultFrame;
        sf::Vector2f size;
        std::unique_ptr<CollisionPhysics> collisionPhysics;
        std::unique_ptr<AnimationPlayer> animPlayer;
        sf::Vector2f pos;
        bool isBlocking = collisionPhysics->isBlocking();
        bool hasShadow;
        float rotationAngle = static_cast<float>(hash2ValuesModSize(pos.x, pos.y * PRIME, 360));
    };

    Prop(PropOptions config);

    void update(float dt) override;

    void accept(EntityVisitor *visitor) override;

    bool isDecorProp() const;

    bool isPropBlocking() const;

    void renderBy(sf::RenderTarget & renderTarget) override;

    void setIsDecor(bool isDecorProp);

protected:
    EntitySprite &getSprite() override;

    std::unique_ptr<EntitySprite> sprite;
    bool hasDefaultAnim;
    bool isDecor;
    bool isBlocking;
};


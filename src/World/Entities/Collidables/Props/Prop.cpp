

#include "Prop.h"

EntitySprite &Prop::getSprite() {
    return sprite;
}

void Prop::update(float dt) {
    if (hasDefaultAnim) {
        animPlayer->playCurrentAnim();
    }
}

Prop::Prop(const std::string &spriteSheet, const sf::Vector2f &pos,
           const sf::Vector2f &size, std::unique_ptr<CollisionPhysics> collisionPhysics,
           std::unique_ptr<AnimationPlayer> animPlayer, const sf::IntRect &defaultFrame)
        : sprite(spriteSheet, pos, size / 2.f, defaultFrame),
          CollidableEntity(CollidableEntity::initializeHitbox(size, pos), std::move(collisionPhysics)),
          animPlayer(std::move(animPlayer)) {
    hasDefaultAnim = this->animPlayer->hasCurrentAnim();
    this->animPlayer->setSprite(&sprite);
}


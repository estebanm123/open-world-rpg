

#include "Prop.h"

EntitySprite &Prop::getSprite() {
    return sprite;
}

void Prop::update(float dt) {
    if (hasDefaultAnim) {
        animPlayer->playCurrentAnim();
    }
}

Prop::Prop(const std::string &spriteSheet,
           const sf::Vector2f &size, const sf::IntRect &defaultFrame, PropOptions config)
        : sprite(spriteSheet, config.pos, size / 2.f, defaultFrame),
          CollidableEntity(CollidableEntity::initializeHitbox(size, config.pos), std::move(config.collisionPhysics)),
          animPlayer(std::move(config.animPlayer)) {
    hasDefaultAnim = this->animPlayer->hasCurrentAnim();
    // todo: decouple
    sprite.rotate(config.rotationAngle);
    hitbox.rotate(config.rotationAngle);
    this->animPlayer->setSprite(&sprite);
}


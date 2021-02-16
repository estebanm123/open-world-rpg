

#include "Prop.h"
#include "../../Sprites/ShadowedRegSprite.h"

EntitySprite &Prop::getSprite() {
    return *sprite; // todo: to refactor
}

void Prop::update(float dt) {
    if (hasDefaultAnim) {
        animPlayer->playCurrentAnim();
    }
}

Prop::Prop(const std::string &spriteSheet,
           const sf::Vector2f &size, const sf::IntRect &defaultFrame, PropOptions config)
        : CollidableEntity(CollidableEntity::initializeHitbox(size, config.pos), std::move(config.collisionPhysics)),
          animPlayer(std::move(config.animPlayer)) {
    hasDefaultAnim = this->animPlayer->hasCurrentAnim();
    // todo: decouple
    sprite = config.hasShadow ? std::make_unique<ShadowedRegSprite>(spriteSheet, config.pos, size / 2.f, defaultFrame)
                              : std::make_unique<RegSprite>(spriteSheet, config.pos, size / 2.f, defaultFrame);
    sprite->rotate(config.rotationAngle);
    hitbox.rotate(config.rotationAngle);
    this->animPlayer->setSprite(sprite.get());
}


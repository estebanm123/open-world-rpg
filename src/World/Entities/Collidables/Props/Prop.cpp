

#include "Prop.h"
#include "../../Sprites/ShadowedSpriteReg.h"

EntitySprite &Prop::getSprite() {
    return *sprite; // todo: to refactor
}

void Prop::update(float dt) {
    if (hasDefaultAnim) {
        sprite->playDefaultAnim();
    }
}

Prop::Prop(const std::string &spriteSheet,
           const sf::Vector2f &size, const sf::IntRect &defaultFrame, PropOptions config)
        : CollidableEntity(CollidableEntity::initializeHitbox(size, config.pos), std::move(config.collisionPhysics)) {
    // todo: decouple
    sprite = config.hasShadow ? std::make_unique<ShadowedSpriteReg>(spriteSheet, config.pos, size / 2.f,
                                                                    std::move(config.animPlayer), defaultFrame)
                              : std::make_unique<SpriteReg>(SpriteReg::Config {spriteSheet, config.pos, size / 3.f,
                                                            std::move(config.animPlayer), defaultFrame});
    hasDefaultAnim = sprite->isAnimated();
    sprite->rotate(config.rotationAngle);
    hitbox.rotate(config.rotationAngle);
}


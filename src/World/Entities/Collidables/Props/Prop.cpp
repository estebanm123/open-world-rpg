

#include "Prop.h"
#include "../../Sprites/ShadowedSpriteReg.h"
#include "../Hitbox/SingleHitbox.h"
#include "../../EntityVisitor/EntityVisitor.h"

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
        : CollidableEntity(std::make_unique<SingleHitbox>(sf::FloatRect {config.pos.x, config.pos.y, size.x, size.y}, config.rotationAngle,
                                        std::move(config.collisionPhysics))) {
    // todo: decouple
    sprite = config.hasShadow ? std::make_unique<ShadowedSpriteReg>(spriteSheet, config.pos, size / 2.f,
                                                                    std::move(config.animPlayer), defaultFrame)
                              : std::make_unique<SpriteReg>(SpriteReg::Config{spriteSheet, config.pos, size / 3.f,
                                                                              std::move(config.animPlayer),
                                                                              defaultFrame});
    hasDefaultAnim = sprite->isAnimated();
    sprite->rotate(config.rotationAngle);
}

void Prop::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}


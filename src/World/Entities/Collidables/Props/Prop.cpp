

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

Prop::Prop(PropOptions config)
        : CollidableEntity(
        std::make_unique<SingleHitbox>(sf::FloatRect{config.pos.x, config.pos.y, config.size.x, config.size.y},
                                       config.rotationAngle, std::move(config.collisionPhysics))) {
    // todo: decouple
    sprite = config.hasShadow ? std::make_unique<ShadowedSpriteReg>(config.spriteSheet, config.pos, config.size / 2.f,
                                                                    std::move(config.animPlayer), config.defaultFrame)
                              : std::make_unique<SpriteReg>(
                    SpriteReg::Config{config.spriteSheet, config.pos, config.size / 2.f,
                                      std::move(config.animPlayer),
                                      config.defaultFrame});
    hasDefaultAnim = sprite->isAnimated();
    sprite->rotate(config.rotationAngle);
}

void Prop::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

void Prop::setIsDecor(bool isDecorProp) {
    Prop::isDecor = isDecorProp;
}

bool Prop::isDecorProp() const {
    return isDecor;
}



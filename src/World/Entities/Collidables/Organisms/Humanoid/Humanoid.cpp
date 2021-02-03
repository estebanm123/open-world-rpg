

#include "Humanoid.h"

Humanoid::Humanoid(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
                   const std::string &spriteSheetHead) : OrganismEntity(initializeHitbox(globalPosition)), sprite(
        spriteSheetBody, spriteSheetHead, globalPosition), isPickingUp(false) {
}


sf::RectangleShape Humanoid::initializeHitbox(const sf::Vector2f &pos) {
    sf::Vector2f hitBoxSize = {animConstants::BASE_FRAME_WIDTH / 2.f, animConstants::BASE_FRAME_HEIGHT / 3.f};
    return CollidableEntity::initializeHitbox(hitBoxSize, pos);
}

EntitySprite &Humanoid::getSprite() {
    return sprite;
}

void Humanoid::move(float dt) {
    MoveableEntity::move(dt);
}

void Humanoid::idle() {
    sprite.playIdleAnim();
    // do stuff like regen stamina
}

void Humanoid::dropCurrentItem() {

}

void Humanoid::useCurrentItem() {

}

void Humanoid::setPickingUp(bool pickingUp) {
    isPickingUp = pickingUp;
}

bool Humanoid::pickingUp() const {
    return isPickingUp;
}

void Humanoid::revertLastMove(bool x, bool y) {
    MoveableEntity::revertLastMove(x, y);
}

void Humanoid::renderBy(sf::RenderTarget & renderer) {
    if (hasMoved()) {
        sprite.playMoveAnim();
    } else {
        sprite.playIdleAnim();
    }
    CollidableEntity::renderBy(renderer);
}

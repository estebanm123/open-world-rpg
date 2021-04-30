#include "./MoveableEntity.h"
#include "../Sprites/EntitySprite.h"
#include "Hitbox/Hitbox.h"
#include "../../../Util/MathExtra.h"

MoveableEntity::MoveableEntity(std::unique_ptr<Hitbox> hitbox)
        : CollidableEntity(std::move(hitbox)), lastMoveOffset({0, 0}) {}

void MoveableEntity::setLookDirection(const sf::Vector2f &direction) {
    lookDirection = direction;
}

const sf::Vector2f &MoveableEntity::getLookDirection() const {
    return lookDirection;
}

bool MoveableEntity::hasMoved() const {
    return lastMoveOffset.x != 0 || lastMoveOffset.y != 0;
}

void MoveableEntity::revertLastMove(bool x, bool y) {
    sf::Vector2f moveToReset = lastMoveOffset;

    if (!x) moveToReset.x = 0;
    if (!y) moveToReset.y = 0;

    getSprite().move(-moveToReset);
    hitbox->move(-moveToReset);
    lastMoveOffset = {!x ? lastMoveOffset.x : 0, !y ? lastMoveOffset.y : 0};
}

sf::Vector2f &MoveableEntity::getLastMoveOffset() {
    return lastMoveOffset;
}

void MoveableEntity::update(float dt) {
    lastMoveOffset = {0, 0};
    move(dt);
}

void MoveableEntity::idle() {
    getSprite().playAnim(&MoveableActions::Idle);
}

void MoveableEntity::renderBy(sf::RenderTarget &renderer) {
    if (getCurrentAction() == nullptr) {
        auto moveAction = hasMoved() ? &MoveableActions::Move : &MoveableActions::Idle;
        setCurrentAction(moveAction);
    }

    CollidableEntity::renderBy(renderer);
}

void MoveableEntity::move(float dt) {
    const auto offset = getMoveOffset() * dt;
    lastMoveOffset = offset;
    getSprite().move(offset);
    hitbox->move(offset);
}

sf::Vector2f MoveableEntity::getMoveOffset() {
    float PLACEHOLDER = 180;
    const auto newOffset = moveDirection * PLACEHOLDER;
    return newOffset;
}

void MoveableEntity::setMoveDirection(const sf::Vector2f &direction) {
    moveDirection = direction;
    if (direction.x != 0 && direction.y != 0) normalize(moveDirection);
}


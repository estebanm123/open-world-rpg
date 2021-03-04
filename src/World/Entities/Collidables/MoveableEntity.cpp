#include "./MoveableEntity.h"
#include "../Sprites/EntitySprite.h"
#include "Hitbox/Hitbox.h"

MoveableEntity::MoveableEntity(std::unique_ptr<Hitbox> hitbox)
        : CollidableEntity(std::move(hitbox)), lastMoveOffset({0,0}) {}

void MoveableEntity::move(float dt) {
    const auto offset = getMoveOffset() * dt;
    lastMoveOffset = offset;
    getSprite().move(offset);
    hitbox->move(offset);
}

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
    lastMoveOffset = {!x? lastMoveOffset.x : 0, !y? lastMoveOffset.y : 0};
}

sf::Vector2f &MoveableEntity::getLastMoveOffset() {
    return lastMoveOffset;
}

void MoveableEntity::update(float dt) {
    lastMoveOffset = {0,0};
}

void MoveableEntity::idle() {
    getSprite().playAnim(&MoveableActions::Idle);
}


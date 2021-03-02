#include "./MoveableEntity.h"
#include "../Sprites/EntitySprite.h"

MoveableEntity::MoveableEntity(const Hitbox &hitbox, std::unique_ptr<CollisionPhysics> collisionPhysics)
        : CollidableEntity(hitbox, std::move(collisionPhysics)), lastMoveOffset({0,0}) {}

void MoveableEntity::setRotation(float angle) {
    Entity::setRotation(angle);
    hitbox.setRotation(angle);
}

void MoveableEntity::rotate(float angle) {
    Entity::rotate(angle);
    hitbox.rotate(angle);
}

void MoveableEntity::setPosition(const sf::Vector2f &pos) {
    Entity::setPosition(pos);
    hitbox.setPosition(pos);
}

void MoveableEntity::move(float dt) {
    const auto offset = getMoveOffset() * dt;
    lastMoveOffset = offset;
    getSprite().move(offset);
    hitbox.move(offset);
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
    hitbox.move(-moveToReset);
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



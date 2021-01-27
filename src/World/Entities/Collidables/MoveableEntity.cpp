#include "./MoveableEntity.h"
#include "../EntitySprite.h"

MoveableEntity::MoveableEntity(const Hitbox &hitbox, std::unique_ptr<CollisionPhysics> collisionPhysics)
        : CollidableEntity(hitbox, std::move(collisionPhysics)) {}

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

sf::Vector2f MoveableEntity::getMoveOffset() {
    return sf::Vector2f();
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

void MoveableEntity::revertLastMove() {
    getSprite().move(-lastMoveOffset);
    hitbox.move(-lastMoveOffset);
    lastMoveOffset = {0, 0};
}

sf::Vector2f & MoveableEntity::getLastMoveOffset() {
    return lastMoveOffset;
}

void MoveableEntity::resetLastMove(bool x, bool y) {
    if (x) lastMoveOffset.x = 0;
    if (y) lastMoveOffset.y = 0;
}



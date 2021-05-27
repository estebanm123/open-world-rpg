#include "./MoveableEntity.h"
#include "../Sprites/EntitySprite.h"
#include "Hitbox/SingleHitbox.h"
#include "../../../Util/MathExtra.h"
#include "../../../Util/Debug/VectorDebug.h"

MoveableEntity::MoveableEntity(Config hitboxes, float initialSpeed)
        : CollidableEntity(std::move(hitboxes)), lastMoveOffset({0, 0}), speed(initialSpeed) {}


bool MoveableEntity::hasMoved() const {
    return lastMoveOffset.x != 0 || lastMoveOffset.y != 0;
}

void MoveableEntity::revertLastMove(bool x, bool y) {
    sf::Vector2f moveToReset = lastMoveOffset;

    if (!x) moveToReset.x = 0;
    if (!y) moveToReset.y = 0;

    getSprite().move(-moveToReset);
    mainHitbox->move(-moveToReset);
    if (secondaryHitboxes) secondaryHitboxes->move(-moveToReset);
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

//    auto receivingMoveDir = getMoveDirection();
//    auto translation = receivingMoveDir * 50.f;
//    auto receivingSize = getSize();
//    auto maxReceivingLength = std::max(receivingSize.x, receivingSize.y);
//    auto pos = getPosition();
//
//    if (getSecondaryHitboxes() != nullptr) {
//        auto centerRayEndPoint = getPosition() + receivingMoveDir * 50.f;
//        auto edgePoint1 = getPosition() + sf::Vector2f{receivingMoveDir.y, -receivingMoveDir.x} * maxReceivingLength / 2.f;
//        auto edgeEndPoint1 = edgePoint1 + translation;
//        auto edgePoint2 = getPosition() + sf::Vector2f{-receivingMoveDir.y, receivingMoveDir.x} * maxReceivingLength / 2.f;
//        auto edgeEndPoint2 =  edgePoint2 + translation;
//        VectorDebug::drawLine(getPosition(), centerRayEndPoint, renderer, sf::Color::Cyan);
//        VectorDebug::drawLine(edgePoint1, edgeEndPoint1, renderer, sf::Color::Cyan);
//        VectorDebug::drawLine(edgePoint2, edgeEndPoint2, renderer, sf::Color::Cyan);
//    }

}

void MoveableEntity::move(float dt) {
    const auto offset = getMoveOffset() * dt;
    lastMoveOffset = offset;
    getSprite().move(offset);
    mainHitbox->move(offset);
    if (secondaryHitboxes) secondaryHitboxes->move(offset);
}

sf::Vector2f MoveableEntity::getMoveOffset() {
    return moveDirection * speed;
}

void MoveableEntity::setMoveDirection(const sf::Vector2f &direction) {
    moveDirection = direction;
    if (direction.x != 0 && direction.y != 0) normalize(moveDirection);
}

sf::Vector2f MoveableEntity::getMoveDirection() const {
    return moveDirection;
}

std::vector<Env::EnvId> &MoveableEntity::getUnpassableEnvs() {
    return unpassableEnvs;
}




#include <iostream>
#include "BlockingPhysics.h"
#include "../MoveableEntity.h"

BlockingPhysics::BlockingPhysics() : CollisionPhysics() {

}

bool isXDistLarger(const sf::Vector2f &vec) {
    return abs(vec.x) > abs(vec.y);
}

bool areVectorsInASharedQuadrant(const sf::Vector2f &a, const sf::Vector2f &b) {
    return (a.x > 0 && b.x > 0) || (a.x < 0 && b.x < 0) || (a.y > 0 && b.y > 0) || (a.y < 0 && b.y < 0);
}

void BlockingPhysics::applyPhysics(CollidableEntity * receivingEntity, MoveableEntity *other) {
    const auto &entityPos = receivingEntity->getPosition();
    const auto &otherPos = other->getPosition();

    auto &lastMoveOffset = other->getLastMoveOffset();
    const auto vecFromOtherToEntity = entityPos - otherPos;

    // check to see if each vec shares a common quadrant
    if (areVectorsInASharedQuadrant(vecFromOtherToEntity, lastMoveOffset)) {
        // if other is going in the dir of entity
        auto isXLarger = isXDistLarger(vecFromOtherToEntity);
        other->revertLastMove(isXLarger, !isXLarger);
        // what about the case where x + y are equal (ie. we're moving in a pure diagonal way)
    }
}
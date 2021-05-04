#pragma once

#include "../MoveableEntity.h"

struct EntityCollisionHandler {

    template<class CollidableEntity>
    static void handleCollision(MoveableEntity * moveable, CollidableEntity *otherCollidable) {
        const auto hitboxes = moveable->getHitbox()->getIntersectingSingleHitboxes(otherCollidable->getHitbox());
        if (hitboxes.first == nullptr || hitboxes.second == nullptr) return; // no collision
        hitboxes.first->handleCollision(moveable, otherCollidable);
        hitboxes.second->handleCollision(otherCollidable, moveable);
    }

};







#include "Collidable.h"
#include "../../Util/CollisionChecker.h"

Collidable::Collidable(const Hitbox &hitbox) : hitbox(hitbox) {
}

bool Collidable::intersect(const Collidable &other) const {
    return CollisionChecker::intersect(hitbox, other.hitbox);
}
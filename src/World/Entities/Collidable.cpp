

#include "Collidable.h"
#include "../../Util/CollisionChecker.h"

Collidable::Collidable(const Hitbox &hitbox) : hitbox(hitbox) {
}

bool Collidable::intersect(const Collidable &other) const {
    return CollisionChecker::intersect(hitbox, other.hitbox);
}

sf::RectangleShape Collidable::initializeHitbox(const sf::Vector2f &size, const sf::Vector2f &pos) {
    sf::RectangleShape hitBox;
    hitBox.setSize(size); // todo: double check this
    hitBox.setPosition(pos.x, pos.y);
    hitBox.setOrigin(size / 2.f);
    return hitBox;
}

const sf::Vector2f &Collidable::getSize() const {
    return hitbox.getSize();
}

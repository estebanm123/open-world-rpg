#include "SingleHitbox.h"
#include "../../../../Util/CollisionChecker.h"
#include "../MoveableEntity.h"

void SingleHitbox::move(const sf::Vector2f &offset) {
    bounds.move(offset);
}

void SingleHitbox::handleCollision(CollidableEntity *receiverEntity, MoveableEntity *movingEntity) {
    // loop over all bounds in moving (don't need to touch receiver for now)
    physics->applyPhysics(receiverEntity, movingEntity);
}

void SingleHitbox::handleCollision(CollidableEntity *receiverEntity, Prop *prop) {
    physics->applyPhysics(receiverEntity, prop);
}

void SingleHitbox::setRotation(float angle) {
    bounds.setRotation(angle);
}

void SingleHitbox::rotate(float angle) {
    bounds.rotate(angle);
}

void SingleHitbox::setPosition(const sf::Vector2f &pos) {
    bounds.setPosition(pos);
}


SingleHitbox::SingleHitbox(const sf::FloatRect &rect, float rotAngle, std::unique_ptr<CollisionPhysics> physics) : size(
        {rect.width, rect.height}), physics(std::move(physics)) {
    bounds.setPointCount(4);
    bounds.setPoint(0, {0, 0});
    bounds.setPoint(1, {rect.width, 0});
    bounds.setPoint(2, {rect.width, rect.height});
    bounds.setPoint(3, {0, rect.height});
    bounds.setOrigin(size / 2.f);
    bounds.setPosition({rect.left, rect.top});
    bounds.rotate(rotAngle);
}

SingleHitbox::SingleHitbox(const sf::ConvexShape &bounds, const sf::Vector2f &size,
                           std::unique_ptr<CollisionPhysics> physics) : bounds(bounds), size(size),
                                                                        physics(std::move(physics)) {
}

std::pair<SingleHitbox *, SingleHitbox *> SingleHitbox::getIntersectingSingleHitboxes(Hitbox *otherHitbox) {
    auto otherIntersectingHitbox = otherHitbox->getIntersectingSingleHitbox(this);
    if (otherIntersectingHitbox == nullptr) {
        // no collision
        return {nullptr, nullptr};
    }

    return {this, otherIntersectingHitbox};
}

SingleHitbox *SingleHitbox::getIntersectingSingleHitbox(SingleHitbox *otherHitbox) {
    return CollisionChecker::intersect(otherHitbox->bounds, bounds) ? this : nullptr;
}

void SingleHitbox::renderBy(sf::RenderTarget &renderer) {
    // (debug)
    bounds.setOutlineColor(sf::Color::Cyan);
    bounds.setFillColor(sf::Color{0, 0, 0, 0});
    bounds.setOutlineThickness(1);
    renderer.draw(bounds);
}

const sf::Vector2f &SingleHitbox::getSize() {
    return size;
}


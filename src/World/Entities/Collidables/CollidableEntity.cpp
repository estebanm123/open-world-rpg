

#include "CollidableEntity.h"

#include <utility>
#include "../../../Util/CollisionChecker.h"
#include "MoveableEntity.h"

#ifdef DEBUG
#define RENDER_HITBOX(renderTargetRef, hitbox)
do {                                        \
    debugRenderHitbox(renderer, hitbox);                                            \
} while (0)
#else
#define RENDER_HITBOX
#endif

void debugRenderHitbox(sf::RenderTarget &renderer, CollidableEntity::Hitbox &hitbox) {
    hitbox.setOutlineColor(sf::Color::Cyan);
    hitbox.setFillColor(sf::Color{0, 0, 0, 0});
    hitbox.setOutlineThickness(1);
    renderer.draw(hitbox);
}

CollidableEntity::CollidableEntity(Hitbox hitbox, std::unique_ptr<CollisionPhysics> collisionPhysics) : hitbox(
        std::move(hitbox)), collisionPhysics(std::move(collisionPhysics)) {
    this->collisionPhysics->setEntity(this);
}

bool CollidableEntity::intersect(const CollidableEntity *other) const {
    return CollisionChecker::intersect(hitbox, other->hitbox);
}

sf::RectangleShape CollidableEntity::initializeHitbox(const sf::Vector2f &size, const sf::Vector2f &pos) {
    sf::RectangleShape hitBox;
    hitBox.setSize(size); // todo: double check this
    hitBox.setPosition(pos.x, pos.y);
    hitBox.setOrigin(size / 2.f);
    return hitBox;
}

const sf::Vector2f &CollidableEntity::getSize() const {
    return hitbox.getSize();
}

void CollidableEntity::handleCollision(MoveableEntity *other) {
    if (intersect(other)) {
        collisionPhysics->applyCollisionPhysics(other);
        // todo: trigger StatEffect?
    }

}

void CollidableEntity::renderBy(sf::RenderTarget &renderer) {
    Entity::renderBy(renderer);
    RENDER_HITBOX(renderer, hitbox);
    debugRenderHitbox(renderer, hitbox); // to comment out
}

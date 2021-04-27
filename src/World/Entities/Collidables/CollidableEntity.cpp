

#include "CollidableEntity.h"
#include <utility>
#include "../../../Util/CollisionChecker.h"
#include "MoveableEntity.h"
#include "Hitbox/SingleHitbox.h"

#ifdef DEBUG
#define RENDER_HITBOX(renderTargetRef, hitbox) \
do {                                        \
    debugRenderHitbox(renderer, hitbox);                                            \
} while (0)
#else
#define RENDER_HITBOX
#endif

void debugRenderHitbox(sf::RenderTarget &renderer, Hitbox *hitbox) {
    if (hitbox) {
        hitbox->renderBy(renderer);
    }
}

CollidableEntity::CollidableEntity(std::unique_ptr<Hitbox> hitbox) : hitbox(std::move(hitbox)) {
}

sf::Vector2f CollidableEntity::getSize() {
    return hitbox->getSize();
}

void CollidableEntity::renderBy(sf::RenderTarget &renderer) {
    Entity::renderBy(renderer);
    RENDER_HITBOX(renderer, hitbox.get());
}

Hitbox *CollidableEntity::getHitbox() const {
    return hitbox.get();
}

void CollidableEntity::setRotation(float angle) {
    Entity::setRotation(angle);
    hitbox->setRotation(angle);
}

void CollidableEntity::rotate(float angle) {
    Entity::rotate(angle);
    hitbox->rotate(angle);
}

void CollidableEntity::setPosition(const sf::Vector2f &pos) {
    Entity::setPosition(pos);
    hitbox->setPosition(pos);
}

void CollidableEntity::analyzeCollision(CollidableEntity &otherEntity) {}

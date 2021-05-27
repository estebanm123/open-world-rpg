

#include "CollidableEntity.h"
#include <utility>
#include "MoveableEntity.h"

#ifdef DEBUG
#define RENDER_HITBOX(renderTargetRef, hitbox, secondaryHitboxes, entity) \
do {                                        \
    debugRenderHitbox(renderer, hitbox, secondaryHitboxes, entity);                                            \
} while (0)
#else
#define RENDER_HITBOX
#endif

void debugRenderHitbox(sf::RenderTarget &renderer, Hitbox *hitbox, MultiHitbox *secondaryHitboxes,
                       CollidableEntity *entity) {
    if (hitbox) {
        hitbox->renderBy(renderer);
    }
    if (secondaryHitboxes) {
        secondaryHitboxes->renderBy(renderer);
    }
}

CollidableEntity::CollidableEntity(Config config) :
        mainHitbox(std::move(config.mainHitbox)),
        secondaryHitboxes(std::move(config.secondaryHitboxes)) {}

SingleHitbox *CollidableEntity::getMainHitbox() {
    return mainHitbox.get();
}

MultiHitbox *CollidableEntity::getSecondaryHitboxes() {
    return secondaryHitboxes == nullptr ? nullptr : secondaryHitboxes.get();
}

sf::Vector2f CollidableEntity::getSize() {
    return mainHitbox->getSize();
}

void CollidableEntity::renderBy(sf::RenderTarget &renderer) {
    Entity::renderBy(renderer);
    RENDER_HITBOX(renderer, mainHitbox.get(), secondaryHitboxes == nullptr ? nullptr : secondaryHitboxes.get(), this);
}

void CollidableEntity::setRotation(float angle) {
    Entity::setRotation(angle);
    mainHitbox->setRotation(angle);
    if (secondaryHitboxes) secondaryHitboxes->setRotation(angle);
}

void CollidableEntity::rotate(float angle) {
    Entity::rotate(angle);
    mainHitbox->rotate(angle);
    if (secondaryHitboxes) secondaryHitboxes->rotate(angle);
}

void CollidableEntity::setPosition(const sf::Vector2f &pos) {
    Entity::setPosition(pos);
    mainHitbox->setPosition(pos);
    if (secondaryHitboxes) secondaryHitboxes->setPosition(pos);
}

void CollidableEntity::analyzeCollision(CollidableEntity *otherEntity) {}
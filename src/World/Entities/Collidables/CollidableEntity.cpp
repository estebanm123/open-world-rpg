

#include "CollidableEntity.h"
#include <utility>
#include "../../../Util/CollisionChecker.h"
#include "MoveableEntity.h"
#include "Hitbox/Hitbox.h"
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
    hitbox->renderBy(renderer);
}

CollidableEntity::CollidableEntity(std::unique_ptr<Hitbox> hitbox) : hitbox(std::move(hitbox)) {
}

//sf::RectangleShape CollidableEntity::initializeHitbox(const sf::FloatRect& rect, float rotAngle) {
//    sf::RectangleShape hitBox;
//    hitBox.setSize(size); // todo: double check this
//    hitBox.setPosition(pos.x, pos.y);
//    hitBox.setOrigin(size / 2.f);
//    return hitBox;
//}

const sf::Vector2f &CollidableEntity::getSize() const {
    return hitbox->getSize();
}

void CollidableEntity::renderBy(sf::RenderTarget &renderer) {
    Entity::renderBy(renderer);
    hitbox->renderBy(renderer); // TODO: remove this temp line
//    RENDER_HITBOX(renderer, hitbox.get());
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


#include "./EntitySprite.h"
#include "Entity.h"

const sf::Vector2f &Entity::getPosition() {
    return getSprite().getPosition();
}

void Entity::setPosition(const sf::Vector2f &pos) {
    getSprite().setPosition(pos);
}

void Entity::setRotation(float angle) {
    getSprite().setRotation(angle);
}

void Entity::rotate(float angle) {
    getSprite().rotate(angle);
}

void Entity::renderBy(sf::RenderTarget &renderer) {
    getSprite().renderBy(renderer);
}

float Entity::getRotationAngle() {
    return getSprite().getRotation();
}

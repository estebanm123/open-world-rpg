
#include "Sprites/EntitySprite.h"
#include "Entity.h"
#include "../../Animation/Action.h"

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
    if (currentAction) {
        getSprite().playAnim(currentAction);
    }
    getSprite().renderBy(renderer);
    resetCurrentAction();
}

float Entity::getRotationAngle() {
    return getSprite().getRotation();
}

Action const *Entity::getCurrentAction() const {
    return currentAction;
}

void Entity::setCurrentAction(Action const *newAction) {
    currentAction = newAction;
}

void Entity::resetCurrentAction() {
    currentAction = nullptr;
}

sf::Vector2f Entity::getSize() {
    return getSprite().getSize();
}

sf::Vector2f Entity::getTopLeftPosition() {
    return getPosition() - getSize() / 2.f;
}

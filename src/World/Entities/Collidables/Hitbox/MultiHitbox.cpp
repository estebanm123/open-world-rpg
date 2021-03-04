#include "MultiHitbox.h"
#include "SingleHitbox.h"

void MultiHitbox::move(const sf::Vector2f &offset) {
    for (auto & hitbox : hitboxes) {
        hitbox->move(offset);
    }
}

void MultiHitbox::handleCollision(CollidableEntity *receiver, MoveableEntity *moving) {
    for (auto & hitbox : hitboxes) {
        hitbox->handleCollision(receiver, moving);
    }
}

void MultiHitbox::handleCollision(CollidableEntity *receiverEntity, Prop *prop) {
    for (auto & hitbox : hitboxes) {
        hitbox->handleCollision(receiverEntity, prop);
    }
}

void MultiHitbox::setRotation(float angle) {
    for (auto & hitbox : hitboxes) {
        hitbox->setRotation(angle);
    }
}

void MultiHitbox::rotate(float angle) {
    for (auto & hitbox : hitboxes) {
        hitbox->rotate(angle);
    }
}

void MultiHitbox::setPosition(const sf::Vector2f &pos) {
    for (auto & hitbox : hitboxes) {
        hitbox->setPosition(pos);
    }
}

std::pair<SingleHitbox *, SingleHitbox *> MultiHitbox::getIntersectingSingleHitboxes(Hitbox *otherHitbox) {
    for (auto & hitbox : hitboxes) {
        auto candidatePair = hitbox->getIntersectingSingleHitboxes(otherHitbox);
        if (candidatePair.first != nullptr && candidatePair.second != nullptr) return {nullptr, nullptr};
    }
    return {nullptr, nullptr};
}

SingleHitbox *MultiHitbox::getIntersectingSingleHitbox(SingleHitbox *otherHitbox) {
    for (auto & hitbox : hitboxes) {
        auto candidateHitbox = hitbox->getIntersectingSingleHitbox(otherHitbox);
        if (candidateHitbox != nullptr) return candidateHitbox;
    }
    return nullptr;
}

void MultiHitbox::renderBy(sf::RenderTarget &renderer) {
    for (auto & hitbox : hitboxes) {
        hitbox->renderBy(renderer);
    }
}

MultiHitbox::MultiHitbox(std::vector<std::unique_ptr<SingleHitbox>> hitboxes) : hitboxes(std::move(hitboxes)) {}

const sf::Vector2f &MultiHitbox::getSize() {
    std::__throw_runtime_error("Not implemented");
}

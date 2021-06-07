#include "MultiHitbox.h"

#include "SingleHitbox.h"

void MultiHitbox::move(const sf::Vector2f &offset) {
	for (auto &hitbox : hitboxes) {
		hitbox->move(offset);
	}
}

void MultiHitbox::handleCollision(CollidableEntity *receiver, MoveableEntity *moving) {
	for (auto &hitbox : hitboxes) {
		hitbox->handleCollision(receiver, moving);
	}
}

void MultiHitbox::handleCollision(CollidableEntity *receiverEntity, Prop *prop) {
	for (auto &hitbox : hitboxes) {
		hitbox->handleCollision(receiverEntity, prop);
	}
}

void MultiHitbox::setRotation(float angle) {
	for (auto &hitbox : hitboxes) {
		hitbox->setRotation(angle);
	}
}

void MultiHitbox::rotate(float angle) {
	for (auto &hitbox : hitboxes) {
		hitbox->rotate(angle);
	}
}

void MultiHitbox::setPosition(const sf::Vector2f &pos) {
	for (auto &hitbox : hitboxes) {
		hitbox->setPosition(pos);
	}
}

void MultiHitbox::renderBy(sf::RenderTarget &renderer) {
	for (auto &hitbox : hitboxes) {
		hitbox->renderBy(renderer);
	}
}

MultiHitbox::MultiHitbox(Hitboxes hitboxes) : hitboxes(std::move(hitboxes)) {}

MultiHitbox::Hitboxes &MultiHitbox::getHitboxes() { return hitboxes; }

void MultiHitbox::addSingleHitbox(std::unique_ptr<SingleHitbox> singleHitbox) {
	hitboxes.push_back(std::move(singleHitbox));
}

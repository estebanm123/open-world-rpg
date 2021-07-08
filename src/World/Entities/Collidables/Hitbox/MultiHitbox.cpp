#include "MultiHitbox.h"

#include "SingleHitbox.h"

void MultiHitbox::move(const sf::Vector2f &offset) {
	for (auto &hitbox : hitboxes) {
		hitbox->move(offset);
	}
}

void MultiHitbox::handleCollision(CollisionInfo<MoveableEntity> &collisionInfo) {
	for (auto &hitbox : hitboxes) {
		collisionInfo.receivingEntityHitbox = hitbox.get();
		hitbox->handleCollision(collisionInfo);
	}
}

void MultiHitbox::handleCollision(CollisionInfo<Prop> &collisionInfo) {
	for (auto &hitbox : hitboxes) {
		collisionInfo.receivingEntityHitbox = hitbox.get();
		hitbox->handleCollision(collisionInfo);
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



#include "SpriteContainer.h"

SpriteContainer::SpriteContainer(std::vector<std::unique_ptr<EntitySprite>> sprites) : sprites(std::move(sprites)) {}

void SpriteContainer::renderBy(sf::RenderTarget &renderer) {
	for (auto &sprite : sprites) {
		sprite->renderBy(renderer);
	}
}

void SpriteContainer::playAnim(const Action *action) {
	for (auto &sprite : sprites) {
		sprite->playAnim(action);
	}
}

void SpriteContainer::playDefaultAnim() {
	for (auto &sprite : sprites) {
		sprite->playDefaultAnim();
	}
}

const sf::Vector2f &SpriteContainer::getPosition() const { return sprites[0]->getPosition(); }

void SpriteContainer::setPosition(const sf::Vector2f &pos) {
	for (auto &sprite : sprites) {
		sprite->setPosition(pos);
	}
}

bool SpriteContainer::notCurrentlyPlayingAnim() {
	for (auto &sprite : sprites) {
		if (sprite->notCurrentlyPlayingAnim()) return true;
	}
	return false;
}

float SpriteContainer::getRotation() const { return sprites[0]->getRotation(); }

void SpriteContainer::setRotation(float angle) {
	for (auto &sprite : sprites) {
		sprite->setRotation(angle);
	}
}

void SpriteContainer::move(const sf::Vector2f &offset) {
	for (auto &sprite : sprites) {
		sprite->move(offset);
	}
}

bool SpriteContainer::isAnimated() {
	for (auto &sprite : sprites) {
		if (sprite->isAnimated()) {
			return true;
		}
	}

	return false;
}

sf::Vector2f SpriteContainer::getSize() { return sprites[0]->getSize(); }

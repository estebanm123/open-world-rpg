#pragma once

#include <SFML/Graphics.hpp>

#include "CollisionInfo.h"
#include "Hitbox.h"

class SingleHitbox;

// Proxy for a collection of a Hitboxes
class MultiHitbox : public Hitbox {
public:
	typedef std::vector<std::unique_ptr<SingleHitbox>> Hitboxes;

	MultiHitbox(Hitboxes hitboxes);

	void move(const sf::Vector2f &offset) override;

	void handleCollision(CollisionInfo<MoveableEntity> &collisionInfo) override;

	void handleCollision(CollisionInfo<Prop>&collisionInfo) override;

	void setRotation(float angle) override;

	void rotate(float angle) override;

	void setPosition(const sf::Vector2f &pos) override;

	Hitboxes &getHitboxes();

	void renderBy(sf::RenderTarget &renderer) override;

	void addSingleHitbox(std::unique_ptr<SingleHitbox> singleHitbox);

private:
	Hitboxes hitboxes;
};

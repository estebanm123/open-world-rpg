#pragma once

#include <SFML/Graphics/ConvexShape.hpp>
#include <memory>

#include "../Collision Physics/CollisionPhysics.h"
#include "Hitbox.h"

class SingleHitbox : public Hitbox {
public:
	SingleHitbox(const sf::ConvexShape &bounds,
				 const sf::Vector2f &size,
				 std::unique_ptr<CollisionPhysics> physics = std::make_unique<CollisionPhysics>());

	SingleHitbox(const sf::FloatRect &rect,
				 float rotAngle = 0.f,
				 std::unique_ptr<CollisionPhysics> physics = std::make_unique<CollisionPhysics>());

	void move(const sf::Vector2f &offset) override;

	void handleCollision(CollisionInfo<MoveableEntity> &collisionInfo) override;

	void handleCollision(CollisionInfo<Prop>&collisionInfo) override;

	float getRotation() const;

	void setRotation(float angle) override;

	void rotate(float angle) override;

	const sf::Vector2f &getSize();

	void setPosition(const sf::Vector2f &pos) override;

	void renderBy(sf::RenderTarget &renderer) override;

	const sf::ConvexShape &getBounds() const;

	CollisionPhysics* getCollisionPhysics() const;
private:
	sf::Vector2f size;
	sf::ConvexShape bounds;
	std::unique_ptr<CollisionPhysics> physics;
};

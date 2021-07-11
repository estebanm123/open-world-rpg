#include "SingleHitbox.h"

#include "../../../../Util/CollisionChecker.h"
#include "../MoveableEntity.h"

void SingleHitbox::move(const sf::Vector2f &offset) { bounds.move(offset); }

void SingleHitbox::handleCollision(CollisionInfo<MoveableEntity> &collisionInfo) {
	physics->applyPhysics(collisionInfo);
}

void SingleHitbox::handleCollision(CollisionInfo<Prop>&collisionInfo) {
	physics->applyPhysics(collisionInfo);
}

float SingleHitbox::getRotation() const { bounds.getRotation(); }

void SingleHitbox::setRotation(float angle) { bounds.setRotation(angle); }

void SingleHitbox::rotate(float angle) { bounds.rotate(angle); }

void SingleHitbox::setPosition(const sf::Vector2f &pos) { bounds.setPosition(pos); }

SingleHitbox::SingleHitbox(const sf::FloatRect &rect,
						   float rotAngle,
						   std::unique_ptr<CollisionPhysics> physics)
	: size({rect.width, rect.height}),
	  physics(std::move(physics)) {
	bounds.setPointCount(4);
	bounds.setPoint(0, {0, 0});
	bounds.setPoint(1, {rect.width, 0});
	bounds.setPoint(2, {rect.width, rect.height});
	bounds.setPoint(3, {0, rect.height});
	bounds.setOrigin(size / 2.f);
	bounds.setPosition({rect.left, rect.top});
	bounds.rotate(rotAngle);
}
CollisionPhysics *SingleHitbox::getCollisionPhysics() const { return physics.get(); }

SingleHitbox::SingleHitbox(const sf::ConvexShape &bounds,
						   const sf::Vector2f &size,
						   std::unique_ptr<CollisionPhysics> physics)
	: bounds(bounds),
	  size(size),
	  physics(std::move(physics)) {
	if (bounds.getPointCount() != 4) {
		throw std::runtime_error("only quads are currently supported, due to BlockingPhysics.applyPhysics");
	}
}

void SingleHitbox::renderBy(sf::RenderTarget &renderer) {
	// (debug)
	bounds.setOutlineColor(sf::Color::Cyan);
	bounds.setFillColor(sf::Color{0, 0, 0, 0});
	bounds.setOutlineThickness(1);
	renderer.draw(bounds);
}

const sf::Vector2f &SingleHitbox::getSize() { return size; }

const sf::ConvexShape &SingleHitbox::getBounds() const { return bounds; }

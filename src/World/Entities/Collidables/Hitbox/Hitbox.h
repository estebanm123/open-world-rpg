#pragma once

class CollidableEntity;

class MoveableEntity;

class SingleHitbox;

class Prop;

class Hitbox {
public:
	virtual void move(const sf::Vector2f &offset) = 0;

	virtual void setRotation(float angle) = 0;

	virtual void rotate(float angle) = 0;

	virtual void setPosition(const sf::Vector2f &pos) = 0;

	virtual void renderBy(sf::RenderTarget &renderer) = 0;

	virtual void handleCollision(CollidableEntity *receiver, MoveableEntity *moving) = 0;

	virtual void handleCollision(CollidableEntity *receiver, Prop *prop) = 0;
};
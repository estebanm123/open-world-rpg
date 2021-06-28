#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

class EntitySprite;

class Action;

class EntityVisitor;


class Entity : sf::NonCopyable {
public:
	enum Altitude {
		VERY_LOW = 0,
		LOW = 1,
		MEDIUM = 2,
		HIGH = 3,
		VERY_HIGH = 4
	};

	virtual void renderBy(sf::RenderTarget &renderer);

	virtual void update(float dt) = 0;

	virtual const sf::Vector2f &getPosition();

	virtual void setPosition(const sf::Vector2f &pos);

	virtual sf::Vector2f getSize();

	virtual void setRotation(float angle);

	virtual float getRotationAngle();

	virtual void rotate(float angle);

	virtual ~Entity() = default;

	virtual void accept(EntityVisitor *visitor) = 0;

	sf::Vector2f getTopLeftPosition();

protected:
	virtual EntitySprite &getSprite() = 0;

	void setCurrentAction(Action const *currentAction);

	Action const *getCurrentAction() const;

	void resetCurrentAction();

private:
	Action const *currentAction = nullptr;
	Altitude altitude = MEDIUM;

public:
	Altitude getAltitude() const;
	void setAltitude(Altitude altitude);
};

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

#include "../Entity.h"
#include "Collision Physics/CollisionPhysics.h"
#include "Hitbox/MultiHitbox.h"
#include "Hitbox/SingleHitbox.h"

class MoveableEntity;

class Hitbox;

class CollidableEntity : public Entity {
public:
	struct Config {
		std::unique_ptr<SingleHitbox> mainHitbox;
		std::unique_ptr<MultiHitbox> secondaryHitboxes = nullptr;
		std::unique_ptr<MultiHitbox> tertiaryHitboxes = nullptr;
	};

	typedef std::vector<std::unique_ptr<SingleHitbox>> Hitboxes;

	explicit CollidableEntity(Config config);

	sf::Vector2f getSize() override;

	void setRotation(float angle) override;

	void rotate(float angle) override;

	void setPosition(const sf::Vector2f &pos) override;

	void renderBy(sf::RenderTarget &renderer) override;

	bool isBlocking() const;

	SingleHitbox *getMainHitbox();

	MultiHitbox *getSecondaryHitboxes();

	virtual void analyzeCollision(CollidableEntity *otherEntity);

protected:
	std::unique_ptr<SingleHitbox> mainHitbox;  // checked against each main and secondary hitbox of another collidable
	std::unique_ptr<MultiHitbox> secondaryHitboxes;	 // checked only against main hitbox of other collidable
	std::unique_ptr<MultiHitbox> tertiaryHitboxes;	 // special cases handled by subclass(es)
	bool blocking = false;
};

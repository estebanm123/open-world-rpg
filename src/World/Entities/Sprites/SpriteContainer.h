#pragma once

#include "EntitySprite.h"
#include "SpriteReg.h"

// composite part of composite pattern
class SpriteContainer : public EntitySprite {
public:
	// Order of sprites is render order
	explicit SpriteContainer(std::vector<std::unique_ptr<EntitySprite>> sprites,
							 bool overridePos,
							 sf::Vector2f customCenterPos);

	void renderBy(sf::RenderTarget &renderer) override;

	void playAnim(Action const *action) override;

	bool isAnimated() override;

	sf::Vector2f getSize() override;

	void playDefaultAnim() override;

	// TODO: set animPlayers?

	const sf::Vector2f &getPosition() const override;

	void setPosition(const sf::Vector2f &pos) override;

	float getRotation() const override;

	void setRotation(float angle) override;

	void move(const sf::Vector2f &offset) override;

	bool notCurrentlyPlayingAnim() override;

private:
	std::vector<std::unique_ptr<EntitySprite>> sprites;
	bool overridePos;
	sf::Vector2f customCenterPos;
};

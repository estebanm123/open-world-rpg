#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "../../../Animation/Animation.h"
#include "../../../Animation/AnimationPlayer.h"
#include "./EntitySprite.h"

class AnimationPlayer;

class SpriteReg : public EntitySprite {
public:
	struct Config {
		Config(const std::string &spriteSheet,
			   const sf::Vector2f &pos,
			   const sf::Vector2f &origin,
			   std::unique_ptr<AnimationPlayer> animPlayer = nullptr,
			   sf::IntRect defaultFrame = animConstants::EMPTY_FRAME);

		std::string spriteSheet;
		sf::Vector2f pos;
		sf::Vector2f origin;
		std::unique_ptr<AnimationPlayer> animPlayer;
		sf::IntRect defaultFrame;
	};

	struct CopyableConfig {
		const std::string spriteSheet;
		const sf::Vector2f pos;
		const sf::Vector2f origin;
		const sf::IntRect defaultFrame;
	};

	// CONFIG IS NOT USEABLE AFTER
	explicit SpriteReg(Config config);

	explicit SpriteReg(CopyableConfig config);

	sf::Vector2f getSize() override;

	void renderBy(sf::RenderTarget &renderer) override;

	void setTexture(const sf::Texture &texture);

	const sf::IntRect &getTextureRect() const;

	bool isAnimated() override;

	bool notCurrentlyPlayingAnim() override;

	void playAnim(Action const *action) override;

	void playDefaultAnim() override;

	void setAnimPlayer(std::unique_ptr<AnimationPlayer> newAnimPlayer);

	virtual void setTextureRect(const sf::IntRect &rectangle);

	const sf::Vector2f &getPosition() const override;

	void setPosition(const sf::Vector2f &pos) override;

	float getRotation() const override;

	void setRotation(float angle) override;

	void move(const sf::Vector2f &offset) override;

protected:
	sf::Sprite sprite;
	std::unique_ptr<AnimationPlayer> animPlayer;

	void setTextureRectUtil(const sf::IntRect &frame);
};

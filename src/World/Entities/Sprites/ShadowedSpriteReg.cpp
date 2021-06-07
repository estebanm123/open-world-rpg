#include "ShadowedSpriteReg.h"

#include "../../../Animation/AnimationPlayer.h"
#include "../../../Util/SpriteShadowGenerator.h"

const inline auto DEFAULT_SHADOW_OFFSET = 5;
const inline float OFFSET_HEIGHT_PROPORTION = 0.15;

ShadowedSpriteReg::ShadowedSpriteReg(const std::string &spriteSheet,
									 const sf::Vector2f &pos,
									 const sf::Vector2f &origin,
									 std::unique_ptr<AnimationPlayer> animPlayer,
									 float offsetMultiplier,
									 const sf::IntRect &defaultFrame)
	: SpriteReg({spriteSheet, pos, origin, std::move(animPlayer), defaultFrame}),
	  shadow({spriteSheet + SpriteShadowGenerator::SHADOW_SUFFIX, pos, origin, nullptr, defaultFrame}) {
	float offset = defaultFrame.height == 0 ? DEFAULT_SHADOW_OFFSET * offsetMultiplier
											: defaultFrame.height * OFFSET_HEIGHT_PROPORTION * offsetMultiplier;
	shadow.move({offset / 2, offset});
}

void ShadowedSpriteReg::renderBy(sf::RenderTarget &renderer) {
	shadow.renderBy(renderer);
	SpriteReg::renderBy(renderer);
}

void ShadowedSpriteReg::setTextureRect(const sf::IntRect &rectangle) {
	SpriteReg::setTextureRect(rectangle);
	shadow.setTextureRect(rectangle);
}

void ShadowedSpriteReg::setPosition(const sf::Vector2f &pos) {
	SpriteReg::setPosition(pos);
	shadow.setPosition(pos);
}

void ShadowedSpriteReg::setRotation(float angle) {
	SpriteReg::setRotation(angle);
	shadow.setRotation(angle);
}

void ShadowedSpriteReg::move(const sf::Vector2f &offset) {
	SpriteReg::move(offset);
	shadow.move(offset);
}

void ShadowedSpriteReg::playAnim(const Action *action) {
	SpriteReg::playAnim(action);
	shadow.setTextureRect(sprite.getTextureRect());
}

void ShadowedSpriteReg::playDefaultAnim() {
	SpriteReg::playDefaultAnim();
	shadow.setTextureRect(sprite.getTextureRect());
}

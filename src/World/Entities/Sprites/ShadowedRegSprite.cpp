#include "ShadowedRegSprite.h"
#include "../../../Util/SpriteShadowGenerator.h"


const inline auto DEFAULT_SHADOW_OFFSET = 5;
const inline float OFFSET_HEIGHT_PROPORTION = 0.15;

ShadowedRegSprite::ShadowedRegSprite(const std::string &spriteSheet, const sf::Vector2f &pos,
                                     const sf::Vector2f &origin, const sf::IntRect &defaultFrame) : RegSprite(
        spriteSheet, pos, origin, defaultFrame), shadow(spriteSheet + SpriteShadowGenerator::SHADOW_SUFFIX, pos, origin,
                                                        defaultFrame) {
    float offset = defaultFrame.height == 0 ? DEFAULT_SHADOW_OFFSET : defaultFrame.height * OFFSET_HEIGHT_PROPORTION;
    shadow.move({offset / 2, offset});
}

void ShadowedRegSprite::renderBy(sf::RenderTarget &renderer) {
    shadow.renderBy(renderer);
    RegSprite::renderBy(renderer);
}

void ShadowedRegSprite::setTexture(const sf::Texture &texture) {
    RegSprite::setTexture(texture);
}

void ShadowedRegSprite::setTextureRect(const sf::IntRect &rectangle) {
    RegSprite::setTextureRect(rectangle);
    shadow.setTextureRect(rectangle);
}

void ShadowedRegSprite::setPosition(const sf::Vector2f &pos) {
    RegSprite::setPosition(pos);
    shadow.setPosition(pos);
}

void ShadowedRegSprite::setRotation(float angle) {
    RegSprite::setRotation(angle);
    shadow.setRotation(angle);
}

void ShadowedRegSprite::move(const sf::Vector2f &offset) {
    RegSprite::move(offset);
    shadow.move(offset);
}




#include "RegSprite.h"
#include "../../Resource Managers/ResourceHolder.h"

RegSprite::RegSprite(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &origin, const sf::IntRect &defaultFrame) {
    sprite.setTexture(ResourceHolder::get().textures.get(spriteSheet));
    sprite.setOrigin(origin);
    sprite.setPosition(pos);
    if (defaultFrame != animConstants::EMPTY_FRAME) {
        sprite.setTextureRect(defaultFrame);
    }
}

void RegSprite::setTexture(const sf::Texture &texture) {
    sprite.setTexture(texture);
}

const sf::IntRect &RegSprite::getTextureRect() const {
    return sprite.getTextureRect();
}

void RegSprite::setTextureRect(const sf::IntRect &rectangle) {
    sprite.setTextureRect(rectangle);
}

const sf::Vector2f &RegSprite::getPosition() const {
    return sprite.getPosition();
}

void RegSprite::setPosition(const sf::Vector2f &pos) {
    sprite.setPosition(pos);
}

float RegSprite::getRotation() const {
    return sprite.getRotation();
}

void RegSprite::setRotation(float angle) {
    sprite.setRotation(angle);
}

void RegSprite::move(const sf::Vector2f &offset) {
    sprite.move(offset);
}

void RegSprite::renderBy(sf::RenderTarget &renderer) {
    renderer.draw(sprite);
}


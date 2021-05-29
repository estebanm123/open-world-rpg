

#include "SpriteReg.h"
#include "../../../Resource Managers/ResourceHolder.h"
#include "../../../Animation/AnimationPlayer.h"

SpriteReg::SpriteReg(Config config) : animPlayer(
        std::move(config.animPlayer)) {
    sprite.setTexture(ResourceHolder::get().textures.get(config.spriteSheet));
    sprite.setPosition(config.pos);
    sprite.setOrigin(config.origin);
    if (config.defaultFrame != animConstants::EMPTY_FRAME) {
        sprite.setTextureRect(config.defaultFrame);
    }
}
SpriteReg::SpriteReg(CopyableConfig config) : animPlayer(nullptr) {
    sprite.setTexture(ResourceHolder::get().textures.get(config.spriteSheet));
    sprite.setPosition(config.pos);
    sprite.setOrigin(config.origin);
    if (config.defaultFrame != animConstants::EMPTY_FRAME) {
        sprite.setTextureRect(config.defaultFrame);
    }
}

void SpriteReg::setTexture(const sf::Texture &texture) {
    sprite.setTexture(texture);
}

const sf::IntRect &SpriteReg::getTextureRect() const {
    return sprite.getTextureRect();
}

void SpriteReg::setTextureRect(const sf::IntRect &rectangle) {
    sprite.setTextureRect(rectangle);
}

const sf::Vector2f &SpriteReg::getPosition() const {
    return sprite.getPosition();
}

void SpriteReg::setPosition(const sf::Vector2f &pos) {
    sprite.setPosition(pos);
}

float SpriteReg::getRotation() const {
    return sprite.getRotation();
}

void SpriteReg::setRotation(float angle) {
    sprite.setRotation(angle);
}

void SpriteReg::move(const sf::Vector2f &offset) {
    sprite.move(offset);
}

void SpriteReg::renderBy(sf::RenderTarget &renderer) {
    renderer.draw(sprite);
}

void SpriteReg::playAnim(const Action *action) {
    auto &nextFrame = animPlayer->playAnim(action);
    setTextureRectUtil(nextFrame);
}

void SpriteReg::playDefaultAnim() {
    setTextureRectUtil(animPlayer->playCurrentAnim());
}

void SpriteReg::setAnimPlayer(std::unique_ptr<AnimationPlayer> newAnimPlayer) {
    animPlayer = std::move(newAnimPlayer);
}

bool SpriteReg::isAnimated() {
    return animPlayer != nullptr;
}

void SpriteReg::setTextureRectUtil(const sf::IntRect &frame) {
    if (frame != animConstants::EMPTY_FRAME && sprite.getTextureRect() != frame) {
        sprite.setTextureRect(frame);
    }

}

sf::Vector2f SpriteReg::getSize() {
    return {sprite.getGlobalBounds().width, sprite.getLocalBounds().height};
}

SpriteReg::Config::Config(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &origin,
                          std::unique_ptr<AnimationPlayer> animPlayer, const sf::IntRect &defaultFrame) : spriteSheet(
        spriteSheet), pos(pos), origin(origin), animPlayer(std::move(animPlayer)), defaultFrame(defaultFrame) {

}

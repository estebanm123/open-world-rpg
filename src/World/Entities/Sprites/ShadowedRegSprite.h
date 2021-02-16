#pragma once

#include "RegSprite.h"

class ShadowedRegSprite : public RegSprite {
public:
    ShadowedRegSprite(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &origin,
              const sf::IntRect &defaultFrame = animConstants::EMPTY_FRAME);

    void renderBy(sf::RenderTarget &renderer) override;

    void setTexture(const sf::Texture &texture) override;

    void setTextureRect(const sf::IntRect &rectangle) override;

    void setPosition(const sf::Vector2f &pos) override;

    void setRotation(float angle) override;

    void move(const sf::Vector2f &offset) override;
private:
    RegSprite shadow;
};



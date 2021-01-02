#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "./EntitySprite.h"

class RegSprite : public EntitySprite {
public:
    RegSprite(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &origin);

    void renderBy(sf::RenderTarget &renderer) override;

    void setTexture(const sf::Texture &texture) override;

    const sf::IntRect &getTextureRect() const override;

    void setTextureRect(const sf::IntRect &rectangle) override;

    const sf::Vector2f &getPosition() const override;

    void setPosition(const sf::Vector2f &pos) override;

    float getRotation() const override;

    void setRotation(float angle) override;

    void move(const sf::Vector2f &offset) override;

private:
    sf::Sprite sprite;
};





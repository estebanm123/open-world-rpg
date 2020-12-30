#pragma once

#include "./EntitySprite.h"

class RegSprite : public EntitySprite {
    void setTexture(const sf::Texture &texture) override;

    void setTextureRect(const sf::IntRect &rectangle) override;

    const sf::Vector2f &getPosition() const override;

    void setPosition(const sf::Vector2f &pos) override;

    const float getRotation() const override;

    void setRotation(float angle) const override;

    void move(const sf::Vector2f &offset) override;
};





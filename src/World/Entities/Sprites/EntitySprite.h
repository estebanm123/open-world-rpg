#pragma once

#include <SFML/Graphics/Texture.hpp>

class Action;

class EntitySprite {
public:
    virtual void renderBy(sf::RenderTarget &renderer) = 0;

//    virtual void setTextureRect(const sf::IntRect &rectangle) = 0;

    virtual sf::Vector2f getSize() = 0;

    virtual void playAnim(Action const * action) = 0;

    virtual bool isAnimated() = 0;

    virtual void playDefaultAnim() = 0;

    virtual const sf::Vector2f &getPosition() const = 0;

    virtual void setPosition(const sf::Vector2f &pos) = 0;

    virtual float getRotation() const = 0;

    virtual void setRotation(float angle) = 0;

    virtual void rotate(float angle);

    virtual void move(const sf::Vector2f &offset) = 0;

    virtual ~EntitySprite() = default;

};





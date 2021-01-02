#pragma once

#include <SFML/Graphics/Texture.hpp>


class EntitySprite {
public:
    virtual void renderBy(sf::RenderTarget &renderer) = 0;

    virtual void setTexture(const sf::Texture &texture) = 0;

    virtual const sf::IntRect &getTextureRect() const = 0;

    virtual void setTextureRect(const sf::IntRect &rectangle) = 0;

    virtual const sf::Vector2f &getPosition() const = 0;

    virtual void setPosition(const sf::Vector2f &pos) = 0;

    virtual float getRotation() const = 0;

    virtual void setRotation(float angle) = 0;

    virtual void rotate(float angle);

    virtual void move(const sf::Vector2f &offset) = 0;

    virtual ~EntitySprite() = default;


//virtual const sf::Vector2f& getOrigin() const;
//virtual void setOrigin(const sf::Vector2f& origin);


};





#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

class EntitySprite;

class Entity {
public:
    virtual void renderBy(sf::RenderTarget &renderer);

    virtual void update(float dt) = 0;

    virtual const sf::Vector2f &getPosition();

    virtual void setPosition(const sf::Vector2f &pos);

    virtual void setRotation(float angle);

    virtual void rotate(float angle);

    virtual ~Entity() = default;

protected:
    virtual EntitySprite &getSprite() = 0;

};





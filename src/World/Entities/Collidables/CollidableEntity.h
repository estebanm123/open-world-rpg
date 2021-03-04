#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include "Collision Physics/CollisionPhysics.h"
#include "../Entity.h"

class MoveableEntity;

class Hitbox;

class CollidableEntity : public Entity {
public:
    CollidableEntity(std::unique_ptr<Hitbox> hitbox);

    const sf::Vector2f &getSize() const;

    void setRotation(float angle) override;

    void rotate(float angle) override;

    void setPosition(const sf::Vector2f &pos) override;

    void renderBy(sf::RenderTarget &renderer) override;

    Hitbox * getHitbox() const;

protected:
    static sf::RectangleShape initializeHitbox(const sf::Vector2f &size, const sf::Vector2f &pos);

    std::unique_ptr<Hitbox> hitbox;
};





#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include "Collision Physics/CollisionPhysics.h"
#include "../Entity.h"
#include "Hitbox/Hitbox.h"

class MoveableEntity;

class Hitbox;

class CollidableEntity : public Entity {
public:
    explicit CollidableEntity(std::unique_ptr<Hitbox> hitbox);

    sf::Vector2f getSize() override;

    void setRotation(float angle) override;

    void rotate(float angle) override;

    void setPosition(const sf::Vector2f &pos) override;

    void renderBy(sf::RenderTarget &renderer) override;

    Hitbox * getHitbox() const;

    virtual void analyzeCollision(CollidableEntity & otherEntity);

protected:
    std::unique_ptr<Hitbox> hitbox;
};





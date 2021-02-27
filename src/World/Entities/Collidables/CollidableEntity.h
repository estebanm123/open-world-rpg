#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include "Collision Physics/CollisionPhysics.h"
#include "../Entity.h"

class MoveableEntity;

class CollidableEntity : public Entity {
public:
    typedef sf::RectangleShape Hitbox; // todo: refactor to a more complex separate type

    CollidableEntity(Hitbox hitbox, std::unique_ptr<CollisionPhysics> CollisionPhysics);

    void handleCollision(MoveableEntity *other);

    const sf::Vector2f &getSize() const;

    void renderBy(sf::RenderTarget &renderer) override;

protected:
    bool intersect(const CollidableEntity *other) const;

    static sf::RectangleShape initializeHitbox(const sf::Vector2f &size, const sf::Vector2f &pos);

    Hitbox hitbox;
private:
    std::unique_ptr<CollisionPhysics> collisionPhysics;
};





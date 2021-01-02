#pragma once

#include "./Entity.h"
#include "./Collidable.h"

class MoveableEntity : public Entity, public Collidable {
public:
    explicit MoveableEntity(const Hitbox &hitbox);

    // optional delta is intended to be from time since last frame, for purposes of smooth movement
    virtual void move(float dt);

    virtual void idle() = 0;

    void setRotation(float angle) override;

    void rotate(float angle) override;

    void setPosition(const sf::Vector2f &pos) override;

    void setLookDirection(const sf::Vector2f& direction);

    const sf::Vector2f& getLookDirection() const;

    ~MoveableEntity() override = default;

protected:
    virtual sf::Vector2f getMoveOffset();

    sf::Vector2f lookDirection;
};






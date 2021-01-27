#pragma once

#include "../Entity.h"
#include "CollidableEntity.h"

class MoveableEntity : public CollidableEntity {
public:
    explicit MoveableEntity(const Hitbox &hitbox, std::unique_ptr<CollisionPhysics> collisionPhysics);

    // optional delta is intended to be from time since last frame, for purposes of smooth movement
    virtual void move(float dt);

    virtual void idle() = 0;

    void setRotation(float angle) override;

    void rotate(float angle) override;

    void setPosition(const sf::Vector2f &pos) override;

    void setLookDirection(const sf::Vector2f& direction);

    const sf::Vector2f& getLookDirection() const;

    void resetLastMove(bool x, bool y);

    virtual void revertLastMove();

    // approximates cardinal direction of last move (for players, this isn't an approximation)
    sf::Vector2f & getLastMoveOffset();

    bool hasMoved() const;

    ~MoveableEntity() override = default;

protected:
    virtual sf::Vector2f getMoveOffset();

    sf::Vector2f lookDirection;

    sf::Vector2f lastMoveOffset; // offset in dir of last move
};






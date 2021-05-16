#pragma once

#include "CollidableEntity.h"
#include "../../../Animation/Actions.h"

struct MoveableActions : public Actions {
    static constexpr Action Idle {};
    static constexpr Action Move {};
};

class MoveableEntity : public CollidableEntity {
public:
    explicit MoveableEntity(Config hitboxes, float initialVelocity);

    // optional delta is intended to be from time since last frame, for purposes of smooth movement
    virtual void move(float dt);

    // for subclasses this needs to be called first
    void update(float dt) override;

    void idle();

    void renderBy(sf::RenderTarget & renderer) override;

    void setMoveDirection(const sf::Vector2f & direction);

    sf::Vector2f getMoveDirection() const;

    // x indicates revert movement in x dir, and y indicates revert movement in y dir
    virtual void revertLastMove(bool x, bool y);

    // approximates cardinal direction of last move (for players, this isn't an approximation)
    sf::Vector2f &getLastMoveOffset();

    bool hasMoved() const;

    ~MoveableEntity() override = default;

protected:
    virtual sf::Vector2f getMoveOffset();
    float speed;
    sf::Vector2f moveDirection;

private:
    sf::Vector2f lastMoveOffset; // offset in dir of last move
};






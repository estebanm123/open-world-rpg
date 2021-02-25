#pragma once

#include "../Entity.h"
#include "CollidableEntity.h"
#include "../../../Animation/Actions.h"

struct MoveableActions : public Actions {
    static constexpr Action Idle {};
    static constexpr Action Move {};
};

class MoveableEntity : public CollidableEntity {
public:
    explicit MoveableEntity(const Hitbox &hitbox, std::unique_ptr<CollisionPhysics> collisionPhysics);

    // optional delta is intended to be from time since last frame, for purposes of smooth movement
    virtual void move(float dt);

    // for subclasses this needs to be called first
    void update(float dt) override;

    void idle();

    void setRotation(float angle) override;

    void rotate(float angle) override;

    void setPosition(const sf::Vector2f &pos) override;

    void setLookDirection(const sf::Vector2f &direction);

    const sf::Vector2f &getLookDirection() const;

    // x indicates revert movement in x dir, and y indicates revert movement in y dir
    virtual void revertLastMove(bool x, bool y);

    // approximates cardinal direction of last move (for players, this isn't an approximation)
    sf::Vector2f &getLastMoveOffset();

    bool hasMoved() const;

    ~MoveableEntity() override = default;

protected:
    virtual sf::Vector2f getMoveOffset();

    sf::Vector2f lookDirection;

    sf::Vector2f lastMoveOffset; // offset in dir of last move
};






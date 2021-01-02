#pragma once

#include "../Humanoid.h"
#include "./PlayerInputManager.h"


class Player : public Humanoid {
public:
    explicit Player(const sf::Vector2f &globalPosition);

    void update(float dt) override;

    void handleInput(sf::RenderWindow &window);

    const sf::Vector2i &getMoveDirection() const;

    void setMoveDirection(const sf::Vector2i &direction);

    void move(float dt) override;

    ~Player() override = default;

protected:
    sf::Vector2f getMoveOffset() override;

private:
    sf::Vector2i moveDirection;
    PlayerInputManager inputManager;
};







#include "Player.h"
#include "../../../Hitbox/Hitbox.h"
#include "../../../../EntityVisitor/EntityVisitor.h"

Player::Player(const sf::Vector2f &globalPosition) : Humanoid(globalPosition, "Player/Shadow/body32", "Player/head32"),
                                                     inputManager(this) {}

void Player::update(float dt) {
    Humanoid::update(dt);
}

void Player::handleInput(sf::RenderWindow &window) {
    inputManager.handleInput(window);
}

void Player::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

constexpr float DIAGONAL_SPEED_MULTIPLIER = 0.707f;



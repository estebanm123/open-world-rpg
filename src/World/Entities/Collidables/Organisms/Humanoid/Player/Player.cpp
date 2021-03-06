

#include "Player.h"
#include "../../../../../../Util/MathExtra.h"
#include "../../../Hitbox/Hitbox.h"

Player::Player(const sf::Vector2f &globalPosition) : Humanoid(globalPosition, "Player/Shadow/body32", "Player/head32"),
                                                     inputManager(*this) {}

void Player::update(float dt) {
    Humanoid::update(dt);
}

void Player::handleInput(sf::RenderWindow &window) {
    inputManager.handleInput(window);
}

constexpr float DIAGONAL_SPEED_MULTIPLIER = 0.707f;



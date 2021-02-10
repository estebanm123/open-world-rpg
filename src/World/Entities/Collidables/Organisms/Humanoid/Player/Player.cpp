

#include "Player.h"
#include "../../../../../../Util/MathExtra.h"

Player::Player(const sf::Vector2f &globalPosition) : Humanoid(globalPosition, "Player/body32", "Player/head32"),
                                                     inputManager(*this) {}

const sf::Vector2i &Player::getMoveDirection() const {
    return moveDirection;
}

void Player::setMoveDirection(const sf::Vector2i &direction) {
    moveDirection = direction;
}

void Player::update(float dt) {
    Humanoid::update(dt);
    move(dt);
}

void Player::handleInput(sf::RenderWindow &window) {
    inputManager.handleInput(window);
}

constexpr float DIAGONAL_SPEED_MULTIPLIER = 0.707f;

sf::Vector2f Player::getMoveOffset() {
    int PLACEHOLDER = 200;
    const auto newOffset = moveDirection * PLACEHOLDER;
    sf::Vector2f castedOffset = {static_cast<float>(newOffset.x), static_cast<float>(newOffset.y)};
    if (isDiagonal(moveDirection)) {
        castedOffset *= DIAGONAL_SPEED_MULTIPLIER;
    }
    return castedOffset;
}

void Player::move(float dt) {
    Humanoid::move(dt);
}

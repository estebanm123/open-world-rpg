

#include "Player.h"

Player::Player(const sf::Vector2f &globalPosition) : Humanoid(globalPosition, "Player/body32", "Player/head32"), inputManager(*this) {}

const sf::Vector2i & Player::getMoveDirection() const {
    return moveDirection;
}

void Player::setMoveDirection(const sf::Vector2i& direction) {
    moveDirection = direction;
}

void Player::update(float dt) {
    move(dt);
}

void Player::handleInput(sf::RenderWindow& window) {
    inputManager.handleInput(window);
}

sf::Vector2f Player::getMoveOffset() {
    int PLACEHOLDER = 500;
    const auto newOffset = moveDirection * PLACEHOLDER;
    const sf::Vector2f castedOffset = {static_cast<float>(newOffset.x), static_cast<float>(newOffset.y)};
    return castedOffset;
}

void Player::move(float dt) {
    if (moveDirection.x == 0 & moveDirection.y == 0) {
        sprite.playIdleAnim();
    } else {
        Humanoid::move(dt);
    }

}

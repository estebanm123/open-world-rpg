#include "PlayerInputManager.h"

#include <iostream>

#include "Player.h"

PlayerInputManager::PlayerInputManager(Player &player) : player(player) {

}

void PlayerInputManager::handleInput(sf::RenderWindow &window) {
    handleKeyPresses();
    handleMouseMovement(window);
    handleMouseClicks();
}

void PlayerInputManager::handleMouseClicks() {
    if (!player.firing && !player.pickingUp) handleFiring();
}

void PlayerInputManager::handleFiring() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.curWeapon) {
        if (player.curWeapon->attack()) {
            player.firing = true;
            player.sprite.enableLock();
        }
    }
}

void PlayerInputManager::handleMouseMovement(sf::RenderWindow &window) {
    auto playerPos = player.sprite.getPosition();
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    auto mouseDirRelativeToPlayer = mousePos - playerPos;
    player.lookDirection = mouseDirRelativeToPlayer;
    player.rotatePlayerSprite(mouseDirRelativeToPlayer);

    // for debugging 
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        std::cout << "Mouse: " << mousePos.x << ", " << mousePos.y << std::endl;
        std::cout << "Player: " << playerPos.x << ", " << playerPos.y << std::endl;
    }
}

void PlayerInputManager::handleKeyPresses() {
    handleMovement();
    if (!player.firing) handleWeaponInteractions();
}

void PlayerInputManager::handleWeaponInteractions() {
    handleDropWeapon();
    handlePickUpWeapon();
}

void PlayerInputManager::handleDropWeapon() {
    if (player.curWeapon && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
        std::shared_ptr<Weapon> empty;
        player.setWeapon(empty);
    }
}

void PlayerInputManager::handlePickUpWeapon() {
    player.pickingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);

}


void PlayerInputManager::handleMovement() {
    using Key = sf::Keyboard::Key;
    auto &velocity = player.velocity;
    auto &sprite = player.sprite;

    const auto aPressed = sf::Keyboard::isKeyPressed(Key::A);
    const auto dPressed = sf::Keyboard::isKeyPressed(Key::D);
    const auto sPressed = sf::Keyboard::isKeyPressed(Key::S);
    const auto wPressed = sf::Keyboard::isKeyPressed(Key::W);

    if (wPressed) {
        velocity.x = 0;
        velocity.y = -Player::WALK_SPEED;
        if (dPressed) {
            sprite.playTopRightDiagonalAnim();
            velocity.x = Player::WALK_SPEED;
        } else if (aPressed) {
            sprite.playTopLeftDiagonalAnim();
            velocity.x = -Player::WALK_SPEED;
        } else {
            sprite.playVerticalAnim();
        }
    } else if (sPressed) {
        velocity.x = 0;
        velocity.y = Player::WALK_SPEED;
        if (dPressed) {
            sprite.playTopLeftDiagonalAnim();
            velocity.x = Player::WALK_SPEED;
        } else if (aPressed) {
            sprite.playTopRightDiagonalAnim();
            velocity.x = -Player::WALK_SPEED;
        } else {
            sprite.playVerticalAnim();
        }
    } else if (aPressed) {
        velocity.y = 0;
        sprite.playHorizontalAnim();
        velocity.x = -Player::WALK_SPEED;
    } else if (dPressed) {
        velocity.y = 0;
        sprite.playHorizontalAnim();
        velocity.x = Player::WALK_SPEED;
    } else {
        sprite.resetMoveAnim();
        sprite.playIdleAnim();
        velocity.y = 0;
        velocity.x = 0;
    }
}
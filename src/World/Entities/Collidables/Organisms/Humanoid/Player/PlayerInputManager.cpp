
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>

#include "../../../../../../Util/MathExtra.h"
#include "Player.h"

using Key = sf::Keyboard::Key;

PlayerInputManager::PlayerInputManager(Player *player) : player(player) {}

void PlayerInputManager::handleInput(sf::RenderWindow &window) {
	handleKeyPresses();
	handleMouseMovement(window);
	handleMouseClicks();
}

void PlayerInputManager::handleKeyPresses() {
	handleMovement();
	handleItemKeyPresses();
}

void PlayerInputManager::handleItemKeyPresses() { handlePickUpItem(); }

void PlayerInputManager::handlePickUpItem() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		player->attemptPickup();
	};
}

void PlayerInputManager::handleMovement() {
	const auto aPressed = sf::Keyboard::isKeyPressed(Key::A);
	const auto dPressed = sf::Keyboard::isKeyPressed(Key::D);
	const auto sPressed = sf::Keyboard::isKeyPressed(Key::S);
	const auto wPressed = sf::Keyboard::isKeyPressed(Key::W);

	sf::Vector2f newMoveDir;

	if (wPressed) {
		newMoveDir.y = -1;
	}
	if (sPressed) {
		newMoveDir.y = 1;
	}
	if (aPressed) {
		newMoveDir.x = -1;
	}
	if (dPressed) {
		newMoveDir.x = 1;
	}
	player->setMoveDirection(newMoveDir);
}

void PlayerInputManager::handleMouseMovement(sf::RenderWindow &window) {
	auto playerPos = player->getPosition();
	auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	auto mouseDirRelativeToPlayer = mousePos - playerPos;
	const auto mouseAngle = toDegrees(atan2(mouseDirRelativeToPlayer.x, mouseDirRelativeToPlayer.y));
	player->setRotation(-mouseAngle);

	static sf::Clock timer;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && timer.getElapsedTime().asMilliseconds() > 500) {
		timer.restart();
		std::cout << "\nMouse:  " << std::round(mousePos.x) << "," << std::round(mousePos.y) << std::endl;
		std::cout << "Player: " << std::round(playerPos.x) << "," << std::round(playerPos.y) << std::endl;
	}
}

void PlayerInputManager::handleMouseClicks() {}

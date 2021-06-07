#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Player;

class PlayerInputManager {
public:
	PlayerInputManager(Player *player);

	void handleInput(sf::RenderWindow &window);

private:
	void handleKeyPresses();

	void handleMouseMovement(sf::RenderWindow &window);

	void handleMouseClicks();

	void handleItemKeyPresses();

	void handlePickUpItem();

	void handleMovement();

	Player *player;
};

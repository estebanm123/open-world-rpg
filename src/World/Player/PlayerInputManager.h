#pragma once

class Player;

namespace sf {
	class RenderWindow;
}

class PlayerInputManager
{
public:
	PlayerInputManager(Player& player);
	void handleInput(sf::RenderWindow& window);
private:
	void handleKeyPresses();
	void handleMouseMovement(sf::RenderWindow& window);
	void handleMouseClicks();
	void handleFiring();
	void handleMovement();
	void handleWeaponInteractions();
	void handleDropWeapon();
	void handlePickUpWeapon();
	Player& player;
};

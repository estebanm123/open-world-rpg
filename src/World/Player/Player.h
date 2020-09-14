#pragma once

#include "../Characters/CharacterStats.h"
#include "PlayableHumanoidSprite.h"
#include "../Weapons/Weapon.h"
#include "PlayerInputManager.h"

class Player
{
public:
	Player(sf::Vector2f pos);
	void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
	void renderBy(sf::RenderTarget& renderer) const;
	void handleInput(sf::RenderWindow& window);
	void update(float dt);
	void setWeapon(const std::shared_ptr<Weapon>& newWeapon);
	void die();
	sf::CircleShape getPickUpLimit() const;
	bool isPickingUp() const;
	bool isFiring() const;
	sf::Vector2f getLookDirection();
	const sf::RectangleShape& getHitBox() const;
	
	static constexpr float WALK_SPEED = 400;
	static constexpr float PICK_UP_RADIUS = 20;
	static constexpr float DEFAULT_HEALTH = 100;

private:
	void calculateLookDirection();
	void rotatePlayerSprite(const sf::Vector2f& mouseDirRelativeToPlayer);
	PlayableHumanoidSprite sprite;
	CharacterStats stats;
	sf::Vector2f velocity;
	sf::Vector2f lookDirection;
	std::shared_ptr<Weapon> curWeapon;
	sf::CircleShape pickUpLimit;
	bool pickingUp;
	bool firing;
	bool dead;
	bool isIdle;
	friend class PlayerInputManager;
	PlayerInputManager inputManager;
};


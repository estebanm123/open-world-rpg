

#include "Player.h"

#include "../../../../EntityVisitor/EntityVisitor.h"
#include "../../../Hitbox/Hitbox.h"

Player::Player(const sf::Vector2f &globalPosition)
	: Humanoid(globalPosition, "Player/Shadow/body32", "Player/head32", INITIAL_SPEED),
	  inputManager(this) {}

void Player::update(float dt) { Humanoid::update(dt); }

void Player::handleInput(sf::RenderWindow &window) { inputManager.handleInput(window); }

void Player::accept(EntityVisitor *visitor) { visitor->visit(this); }


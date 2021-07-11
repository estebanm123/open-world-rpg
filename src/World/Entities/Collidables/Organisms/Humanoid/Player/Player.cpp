

#include "Player.h"

#include "../../../../../../Game.h"
#include "../../../../EntityVisitor/EntityVisitor.h"
#include "../../../Hitbox/Hitbox.h"

Player::Player(const sf::Vector2f &globalPosition)
	: Humanoid(globalPosition, "Player/Shadow/body32", "Player/head32", INITIAL_SPEED),
	  inputManager(this) {}

void Player::update(float dt) { Humanoid::update(dt); }

void Player::handleInput(sf::RenderWindow &window) { inputManager.handleInput(window); }

void Player::accept(EntityVisitor *visitor) { visitor->visit(this); }
void Player::renderBy(sf::RenderTarget &renderer) {
	Humanoid::renderBy(renderer);
#ifdef DEBUG
	for (auto debugLine : debugLines) {
		debugLine->color = sf::Color::Cyan;
		auto x = debugLine->color;
		renderer.draw(debugLine, 2, sf::Lines);
	}
//		auto rect = sf::RectangleShape{{100, 100}};
//		rect.setPosition(getPosition());
//		rect.setFillColor(sf::Color{255, 32, 60});
//		renderer.draw(rect);
	debugLines.clear();
#endif
}

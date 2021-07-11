#include "StatePlaying.h"

#include <iostream>

#include "../Game.h"

StatePlaying::StatePlaying(Game &game)
	: StateBase(game),
	  worldView(new sf::View(sf::Vector2f(0, 0), sf::Vector2f(CAMERA_RES_X, CAMERA_RES_Y))),
	  hudView(new sf::View(sf::Vector2f(0, 0), sf::Vector2f(CAMERA_RES_X, CAMERA_RES_Y))),
	  world(worldView),
	  fpsCounter(
	   {CAMERA_RES_X / 2.f - FPS_COUNTER_OFFSET_X, -CAMERA_RES_Y / 2.f + FPS_COUNTER_OFFSET_Y}) {}

void StatePlaying::handleEvent(sf::Event e) {}

void StatePlaying::handleInput() {
	// view set size
	world.handleInput(Game::getWindow());
}

void StatePlaying::update(sf::Time deltaTime) {
	world.update(deltaTime.asSeconds());
	fpsCounter.update();
}

void StatePlaying::fixedUpdate(sf::Time deltaTime) {}

void StatePlaying::render(sf::RenderTarget &renderer) {
	renderer.setView(*worldView);
	world.renderBy(renderer);
	renderer.setView(*hudView);
	fpsCounter.renderBy(renderer);
	renderer.setView(*worldView);
}

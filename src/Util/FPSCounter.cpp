#include "FPSCounter.h"

#include <iostream>

#include "../Resource Managers/ResourceHolder.h"

FPSCounter::FPSCounter(sf::Vector2f pos = {0, 0}) {
	text.move(0, 0);
	text.setOutlineColor(sf::Color::Black);
	text.setFillColor({255, 255, 255});
	text.setOutlineThickness(1);
	text.setFont(ResourceHolder::get().fonts.get("arial"));
	text.setCharacterSize(10);
	text.setPosition(pos);
}

void FPSCounter::setPosition(sf::Vector2f pos) { text.setPosition(pos); }

void FPSCounter::update() {
	frameCount++;

	if (delayTimer.getElapsedTime().asSeconds() > 0.2) {
		fps = frameCount / fpsTimer.restart().asSeconds();
		frameCount = 0;
		delayTimer.restart();
	}
}

void FPSCounter::renderBy(sf::RenderTarget &renderer) {
	text.setString("FPS " + std::to_string(static_cast<int>(fps)));
	renderer.draw(text);
}

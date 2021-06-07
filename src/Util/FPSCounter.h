#pragma once

#include <SFML/Graphics.hpp>

class FPSCounter {
public:
	FPSCounter(sf::Vector2f pos);

	void setPosition(sf::Vector2f pos);

	void update();

	void renderBy(sf::RenderTarget &renderer);

private:
	sf::Text text;
	sf::Clock delayTimer;
	sf::Clock fpsTimer;

	float fps = 0;
	int frameCount = 0;
};
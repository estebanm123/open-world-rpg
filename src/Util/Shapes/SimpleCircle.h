#pragma once

#include <SFML/System.hpp>

struct SimpleCircle {
	SimpleCircle(float radius, const sf::Vector2f &center);

	float radius;
	sf::Vector2f center;
};

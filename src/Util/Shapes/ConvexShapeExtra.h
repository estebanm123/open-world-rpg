#pragma once

#include <SFML/Graphics.hpp>

#include "Edge.h"

struct ConvexShapeExtra {
	static std::vector<sf::Vector2f> getGlobalPoints(const sf::ConvexShape& a);
	static std::vector<GlobalEdge> getGlobalEdges(const sf::ConvexShape& a);
};

#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Shapes/Edge.h"
#include "Shapes/SimpleCircle.h"

namespace sf {
class RectangleShape;
}

struct CollisionChecker {
	static bool intersect(const sf::CircleShape &circle, const sf::FloatRect &rect);

	static bool intersect(const SimpleCircle &circle, sf::Vector2f point);

	// runtime: O(n) where n = num edges in convex polygon; only use for few edges (there's another faster soln for high
	// # edges)
	static bool intersect(const sf::ConvexShape &a, const GlobalEdge &edge);

	// SAT
	static bool intersect(const sf::ConvexShape &a, const sf::ConvexShape &b);
};

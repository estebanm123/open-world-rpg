#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf {
	class RectangleShape;
}

class CollisionChecker
{
public:
	static bool intersect(const sf::CircleShape & circle, const sf::FloatRect & rect);
	static bool intersect(const sf::CircleShape& circle, const sf::RectangleShape& rectShape);
	static bool intersect(const sf::RectangleShape& rectShape1, const sf::RectangleShape& rectShape2);
	static sf::FloatRect convertToFloatRect(const sf::RectangleShape& rect);

};



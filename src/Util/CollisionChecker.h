#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "Shapes/SimpleCircle.h"


namespace sf {
    class RectangleShape;
}

struct CollisionChecker {
    static bool intersect(const sf::CircleShape &circle, const sf::FloatRect &rect);

    static bool intersect(const sf::CircleShape &circle, const sf::RectangleShape &rectShape);

    static bool intersect(const SimpleCircle &circle, sf::Vector2f point);

    static bool intersect(const sf::RectangleShape &rectShape1, const sf::RectangleShape &rectShape2);

    // SAT
    static bool intersect(const sf::ConvexShape &a, const sf::ConvexShape &b);

    static sf::FloatRect convertToFloatRect(const sf::RectangleShape &rect);
};



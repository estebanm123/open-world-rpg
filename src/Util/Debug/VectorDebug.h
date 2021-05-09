#pragma once


#include <SFML/System.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

struct VectorDebug {
    static void drawLine(sf::Vector2f point1, sf::Vector2f point2, sf::RenderTarget &renderer, sf::Color color);
};





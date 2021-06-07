

#include "VectorDebug.h"

void VectorDebug::drawLine(sf::Vector2f point1, sf::Vector2f point2, sf::RenderTarget &renderer, sf::Color color) {
	sf::Vertex line[] = {sf::Vertex(point1, color), sf::Vertex(point2, color)};

	renderer.draw(line, 2, sf::Lines);
}

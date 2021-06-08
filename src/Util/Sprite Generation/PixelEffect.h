#pragma once

#include <SFML/Graphics/Image.hpp>
class PixelEffect {
public:
	virtual void applyPixelEffect(sf::Image &canvas) = 0;
};

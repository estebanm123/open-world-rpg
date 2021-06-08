

#include "ColorChangerPixelEffect.h"

void ColorChangerPixelEffect::applyPixelEffect(sf::Image& canvas) {
	auto size = canvas.getSize();
	for (unsigned int x = 0; x < size.x; x++) {
		for (unsigned int y = 0; y < size.y; y++) {
			auto pixel = canvas.getPixel(x, y);
			canvas.setPixel(x, y, sf::Color(pixel.r + 50, pixel.b + 50, pixel.g + 50, pixel.a));
		}
	}
}

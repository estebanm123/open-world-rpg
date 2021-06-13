

#include "ShadowPixelEffect.h"

const inline auto SHADOW_OPACITY = 50;

void ShadowPixelEffect::applyPixelEffect(sf::Image &canvas) {
	auto size = canvas.getSize();
	for (unsigned int x = 0; x < size.x; x++) {
		for (unsigned int y = 0; y < size.y; y++) {
			auto pixel = canvas.getPixel(x, y);
			if (pixel.a != 0) {
				sf::Color shadow{sf::Color::Black};
				shadow.a = pixel.a >= SHADOW_OPACITY ? SHADOW_OPACITY : pixel.a;
				canvas.setPixel(x, y, shadow);
			}
		}
	}
}

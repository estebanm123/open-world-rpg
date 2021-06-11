

#include "ColorChangerPixelEffect.h"

#include "../Debug/DebugPrint.h"
#include "ColorFrequencyCounter.h"
#include "SpriteGeneratorManager.h"

sf::Uint8 updateRgbComponentBasedOnLimits(int val) {
	return abs(val) % 256;
}

sf::Color ColorChangerPixelEffect::generateUpdatedColor(sf::Color oldColor) const {
	auto newR = updateRgbComponentBasedOnLimits((int) oldColor.r + rChange);
	auto newG = updateRgbComponentBasedOnLimits((int) oldColor.g + gChange);
	auto newB = updateRgbComponentBasedOnLimits((int) oldColor.b + bChange);
	return sf::Color{newR, newG, newB, oldColor.a};
}


void ColorChangerPixelEffect::applyPixelEffect(sf::Image& canvas) {
	auto sortedColors = ColorFrequencyCounter::sortColorsByFrequency(canvas);
	for (auto & pair : sortedColors) {
		DebugPrint::print(pair.first);
		std::cout << " - freq: " << pair.second << std::endl;
	}

	auto size = canvas.getSize();
	for (unsigned int x = 0; x < size.x; x++) {
		for (unsigned int y = 0; y < size.y; y++) {
			auto pixel = canvas.getPixel(x, y);
			if (pixel.a != 0) {
				canvas.setPixel(x, y, generateUpdatedColor(pixel));
			}
		}
	}
}

ColorChangerPixelEffect::ColorChangerPixelEffect(int rChange, int gChange, int bChange)
	: rChange(rChange),
	  gChange(gChange),
	  bChange(bChange) {}

void initializeComponentSemiRandomly(int changeAmount, int & target, bool overrideRandomness) {
	auto shouldDecrement = SpriteGeneratorManager::rand.getIntInRange(0,1);
	if (shouldDecrement || overrideRandomness) {
		target = -changeAmount;
	} else {
		target = changeAmount;
	}
}

ColorChangerPixelEffect::ColorChangerPixelEffect(int changeAmount, bool overrideRandomness) {
	initializeComponentSemiRandomly(changeAmount, rChange, overrideRandomness);
	initializeComponentSemiRandomly(changeAmount, gChange, overrideRandomness);
	initializeComponentSemiRandomly(changeAmount, bChange, overrideRandomness);
}

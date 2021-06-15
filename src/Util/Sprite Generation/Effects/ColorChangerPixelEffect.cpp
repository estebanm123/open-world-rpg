

#include "ColorChangerPixelEffect.h"

#include <utility>

#include "../../Debug/DebugPrint.h"
#include "../ColorFrequencyCounter.h"
#include "../SpriteGeneratorManager.h"

sf::Uint8 updateRgbComponentBasedOnLimits(int val) { return abs(val) % 256; }

sf::Color ColorChangerPixelEffect::generateUpdatedColor(sf::Color oldColor) const {
	auto newR = updateRgbComponentBasedOnLimits((int)oldColor.r + rChange);
	auto newG = updateRgbComponentBasedOnLimits((int)oldColor.g + gChange);
	auto newB = updateRgbComponentBasedOnLimits((int)oldColor.b + bChange);
	return sf::Color{newR, newG, newB, oldColor.a};
}

std::unordered_set<ColorInt> ColorChangerPixelEffect::extractSetFromListOfColors(
	const ColorFrequencyCounter::ColorsByFreq& colorsSortedByFreqAsc) {
	//	for (auto& pair : colorsSortedByFreqAsc) {
	//		DebugPrint::print(pair.first);
	//		std::cout << " - freq: " << pair.second << std::endl;
	//	}

	std::unordered_set<ColorInt> colors = {};
	for (auto i = colorsSortedByFreqAsc.rbegin(); i != colorsSortedByFreqAsc.rend(); ++i) {
		auto pair = *i;
		if (minColorFrequencyForEffect > pair.second) break;
		colors.insert(pair.first.toInteger());
	}

	//	for (auto& color : colors) {
	//		DebugPrint::print(sf::Color(color));
	//		DebugPrint::newLine();
	//	}

	return colors;
}

void ColorChangerPixelEffect::applyPixelEffect(sf::Image& canvas) {
	auto targetColors =
		extractSetFromListOfColors(ColorFrequencyCounter::sortColorsByFrequency(canvas));
	targetColors.insert(baseTargetColors.begin(), baseTargetColors.end());

	auto size = canvas.getSize();
	for (unsigned int x = 0; x < size.x; x++) {
		for (unsigned int y = 0; y < size.y; y++) {
			auto pixel = canvas.getPixel(x, y);
			if (isColorValid(pixel, targetColors)) {
				canvas.setPixel(x, y, generateUpdatedColor(pixel));
			}
		}
	}
}

bool ColorChangerPixelEffect::isColorValid(sf::Color color,
										   const std::unordered_set<ColorInt>& targetColors) {
	if (color.a != 0) {
		if (avoidTargetColors) {
			return targetColors.find(color.toInteger()) == targetColors.end();
		} else {
			return targetColors.find(color.toInteger()) != targetColors.end();
		}
	}
	return false;
}

void ColorChangerPixelEffect::initializeComponentChangeRandomly(int maxChange,
																int& target,
																bool overrideRandomness) {
	if (overrideRandomness) {
		target = maxChange;
		return;
	}

	auto shouldDecrement = rand.getIntInRange(0, 1);
	auto changeAmount = rand.getIntInRange(maxChange / 3, maxChange);
	if (shouldDecrement) {
		target = -changeAmount;
	} else {
		target = changeAmount;
	}
}

ColorChangerPixelEffect::ColorChangerPixelEffect(int id,
												 std::vector<ColorInt> targetColors,
												 int minColorFrequencyForTarget,
												 bool overrideRandomness,
												 bool avoidTargetColors)
	: minColorFrequencyForEffect(minColorFrequencyForTarget),
	  avoidTargetColors(avoidTargetColors) {
	baseTargetColors.insert(targetColors.begin(), targetColors.end());
    auto largePrime = 39916801;
    rand = {id * largePrime};
	initializeComponentChangeRandomly(id, rChange, overrideRandomness);
	initializeComponentChangeRandomly(id, gChange, overrideRandomness);
	initializeComponentChangeRandomly(id, bChange, overrideRandomness);
}

#include "ColorFrequencyCounter.h"

#include <iostream>
#include <unordered_map>

#include "../StringExtra.h"

std::string colorToString(sf::Color color) {
	return std::to_string(color.r) + "-" + std::to_string(color.g) + "-" + std::to_string(color.b);
}

sf::Color stringToColor(const std::string & str) {
	sf::Color result;

	auto tokens = StringExtra::split(str, "-");
	result.r = std::stoi(tokens.at(0));
	result.g = std::stoi(tokens.at(1));
	result.b = std::stoi(tokens.at(2));
	return result;
}

ColorFrequencyCounter::ColorsByFreq sortColors(const std::unordered_map<std::string, int>& colorFreqs) {
	ColorFrequencyCounter::ColorsByFreq result;
	for (auto& it : colorFreqs) {
		result.push_back(std::make_pair(stringToColor(it.first), it.second));
	}
	std::sort(result.begin(), result.end(), ColorFrequencyCounter::AscendingFreqComparator{});
	return result;
}

ColorFrequencyCounter::ColorsByFreq ColorFrequencyCounter::sortColorsByFrequency(const sf::Image& canvas) {
	std::unordered_map<std::string, int> colorFrequencies;

	auto size = canvas.getSize();
	for (unsigned int x = 0; x < size.x; x++) {
		for (unsigned int y = 0; y < size.y; y++) {
			auto color = canvas.getPixel(x, y);
			if (color.a == 0) continue;
			auto colorStr = colorToString(color);

			int freq = 1;
			if (colorFrequencies.find(colorStr) != colorFrequencies.end()) {
				auto curFreq = colorFrequencies.at(colorStr);
				freq = curFreq + 1;
			}

			colorFrequencies.insert_or_assign(colorStr, freq);
			auto x = colorFrequencies.at(colorStr);
		}
	}
	return sortColors(colorFrequencies);
}

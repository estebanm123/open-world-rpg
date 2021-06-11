#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <vector>

class ColorFrequencyCounter {
public:
	typedef std::vector<std::pair<sf::Color, int>> ColorsByFreq;

	struct AscendingFreqComparator {
		inline bool operator()(const std::pair<sf::Color, int>& struct1, const std::pair<sf::Color, int>& struct2) {
			return (struct1.second < struct2.second);
		}
	};

	// ignores alpha by default - todo: parameterize
	static ColorsByFreq sortColorsByFrequency(const sf::Image& img);
};

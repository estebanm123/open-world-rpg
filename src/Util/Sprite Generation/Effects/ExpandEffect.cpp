#include "ExpandEffect.h"

#include <array>
#include <unordered_set>

const std::array<sf::Vector2i, 4> directions{sf::Vector2i{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void ExpandEffect::applyPixelEffect(sf::Image& canvas) {
	auto size = canvas.getSize();

	std::vector<std::vector<bool>> pixelsFilled;
	for (unsigned int x = 0; x < size.x; x++) {
		std::vector<bool> row;
		for (unsigned int y = 0; y < size.y; y++) {
			row.push_back(false);
		}
		pixelsFilled.push_back(row);
	}

	for (unsigned int x = 0; x < size.x; x++) {
		for (unsigned int y = 0; y < size.y; y++) {
			auto currentPixel = canvas.getPixel(x, y);
			if (currentPixel.a != 0 && !pixelsFilled[x][y]) {
				for (auto& dir : directions) {
					auto neighborCoords = sf::Vector2i{static_cast<int>(x) + dir.x, static_cast<int>(y) + dir.y};
					if (neighborCoords.x < 0 || neighborCoords.x > size.x || neighborCoords.y < 0 ||
						neighborCoords.y > size.y)
						continue;
					auto neighbor = canvas.getPixel(neighborCoords.x, neighborCoords.y);
					if (neighbor.a == 0) {
						pixelsFilled[neighborCoords.x][neighborCoords.y] = true;
						canvas.setPixel(neighborCoords.x, neighborCoords.y, currentPixel);
					}
				}
			}
		}
	}
}

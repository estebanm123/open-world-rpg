#include "DebugPrint.h"

using namespace std;

void DebugPrint::print(const sf::ConvexShape& shape) {
	const auto pointCount = shape.getPointCount();
	for (auto i = 0; i < pointCount; i++) {
		print(shape.getPoint(i), " ");
	}
	newLine();
}

void DebugPrint::separator() {
	cout << "_";
	newLine();
}

void DebugPrint::newLine() { cout << std::endl; }

void DebugPrint::print(const sf::Color& color) {
	std::cout << to_string(color.r) << " " << to_string(color.g) << " " << to_string(color.b) << " " << to_string(color.a);
}

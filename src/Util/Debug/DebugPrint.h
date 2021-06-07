

#pragma once

#include <SFML/Graphics/ConvexShape.hpp>
#include <iostream>

class DebugPrint {
public:
	static void separator();

	static void newLine();

	static void print(const sf::ConvexShape &s);

	template <typename T>
	static void print(const sf::Vector2<T> &v, const std::string &suffix = "") {
		std::cout << v.x << "," << v.y << suffix;
	}

	template <typename Printable>
	static void print(const std::vector<Printable> &printables) {
		for (const Printable &printable : printables) {
			print(printable);
		}
		newLine();
	}
};

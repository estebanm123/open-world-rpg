

#include "AiDebug.h"

#include <iostream>

#include "Path/NpcPath.h"

void printPoint(NpcPath::Point p) { std::cout << "  " << p.pos.x << ", " << p.pos.y << std::endl; }

void AiDebug::printPath(NpcPath path, const std::string &message) {
	std::cout << "NPC Path details - " << message << std::endl;
	while (!path.isEmpty()) {
		auto targetPoint = path.peekNextPoint();
		printPoint(targetPoint);
		path.dequeueNextPoint();
	}
	std::cout << std::endl;
}

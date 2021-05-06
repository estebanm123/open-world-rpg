

#include <iostream>
#include "AiDebug.h"
#include "Path/NpcPath.h"

void printPoint(NpcPath::Point p) {
    std::cout << "  " << p.x << ", " << p.y << std::endl;
}

void AiDebug::printPath(NpcPath path, const std::string &message) {
    std::cout << "NPC Path details - " << message << std::endl;
    while (!path.isEmpty()) {
        auto targetPoint = path.peekNextPoint();
        printPoint(targetPoint);
        path.dequeueNextPoint();
    }
    std::cout << std::endl;
}


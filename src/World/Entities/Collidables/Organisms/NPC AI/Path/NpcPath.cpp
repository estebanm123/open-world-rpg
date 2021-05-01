

#include <vector>
#include "NpcPath.h"

const sf::Vector2f NpcPath::EMPTY_POINT = {0, 0};

NpcPath::NpcPath(const std::vector<Point> &points) : points(points.begin(), points.end()) {}

void NpcPath::enqueue(NpcPath::Point point) {
    points.push_back(point);
}

void NpcPath::reset() {
    points.clear();
}

void NpcPath::popNextPoint() {
    points.pop_front();
}

NpcPath::Point NpcPath::peekNextPoint() const {
    return points.front();
}

bool NpcPath::isEmpty() const {
    return points.empty();
}


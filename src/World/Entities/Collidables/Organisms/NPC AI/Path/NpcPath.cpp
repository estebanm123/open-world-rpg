

#include <vector>
#include "NpcPath.h"

const sf::Vector2f NpcPath::EMPTY_POINT = {0, 0};

NpcPath::NpcPath(const std::vector<Point> &points) : points(points.begin(), points.end()) {}

void NpcPath::enqueue(NpcPath::Point point) {
    points.push_front(point);
}

void NpcPath::reset() {
    points.clear();
}

void NpcPath::advanceTargetPoint() {
    points.pop_front();
}

NpcPath::Point NpcPath::getTargetPoint() const {
    if (points.size() > 1) {
        return points.at(1);
    } else {
        return points.at(0);
    }
}

NpcPath::Point NpcPath::getLastVisitedPoint() const {
    return points.front();
}

bool NpcPath::hasTargetPoint() const {
    return !noTargetPoint();
}

bool NpcPath::noTargetPoint() const {
    return points.size() <= 1;
}

bool NpcPath::isEmpty() const {
    return points.empty();
}


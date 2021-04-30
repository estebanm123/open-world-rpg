

#include <vector>
#include "NpcPath.h"

const sf::Vector2f NpcPath::EMPTY_POINT = {0, 0};
const NpcPath::Edge NpcPath::EMPTY_EDGE = {EMPTY_POINT, EMPTY_POINT};

NpcPath::NpcPath(const std::vector<Point> &points) : points(points.begin(), points.end()) {}

NpcPath::Edge NpcPath::getCurrentEdge() const {
    if (points.empty()) {
        return EMPTY_EDGE;
    }
    if (noNextPoint()) {
        return makeEdge(points.front(), EMPTY_POINT);
    }
    return makeEdge(points.front(), points.at(1));
}

NpcPath::Edge NpcPath::makeEdge(const sf::Vector2f &first, const sf::Vector2f &second) {
    return std::make_pair(first, second);
}

void NpcPath::enqueue(NpcPath::Point point) {
    points.push_back(point);
}

void NpcPath::reset() {
    points.clear();
}

void NpcPath::advanceToNextPoint() {
    points.pop_front();
}

NpcPath::Point NpcPath::getNextPoint() const {
    if (points.size() > 1) {
        return points.at(1);
    } else {
        return EMPTY_POINT;
    }
}

NpcPath::Point NpcPath::getLastVisitedPoint() const {
    return points.front();
}

bool NpcPath::noNextPoint() const {
    return points.size() == 1;
}

bool NpcPath::hasNextPoint() const {


}

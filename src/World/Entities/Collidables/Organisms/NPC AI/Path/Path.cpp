

#include <vector>
#include "Path.h"

const sf::Vector2f Path::EMPTY_POINT = {0,0};
const Path::Edge Path::EMPTY_EDGE = {EMPTY_POINT, EMPTY_POINT};

Path::Path(const std::vector<Point> &points) : points(points.begin(), points.end()) {}

Path::Edge Path::getCurrentEdge() const {
    auto pointsSize = points.size();
    if (pointsSize == 0) {
        return EMPTY_EDGE;
    }
    if (pointsSize == 1) {
        return makeEdge(points.front(), EMPTY_POINT);
    }
    return makeEdge(points.front(), points.at(1));
}

Path::Edge Path::makeEdge(const sf::Vector2f &first, const sf::Vector2f &second) {
    return std::make_pair(first, second);
}

void Path::enqueue(Path::Point point) {
    points.push_back(point);
}

void Path::reset() {
    points.clear();
}

void Path::advanceToNextPoint() {
    points.pop_front();
}

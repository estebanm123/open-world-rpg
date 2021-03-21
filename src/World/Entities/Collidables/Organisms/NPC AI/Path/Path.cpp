

#include "Path.h"

Path::Path(PathManager *manager, int capacity) : manager(manager), capacity(capacity) {
    if (capacity < 2) {
        throw std::runtime_error("Path capacity not less than 2");
    }
}

Path::Edge Path::getCurrentEdge() const {
    return makeEdge(points.front(), points.at(1));
}

Path::Edge Path::makeEdge(const sf::Vector2f &first, const sf::Vector2f &second) {
    return std::make_pair(first, second);
}

Path::Point Path::peek() const {
    return points.front();
}

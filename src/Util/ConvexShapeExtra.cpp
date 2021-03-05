

#include "ConvexShapeExtra.h"

std::vector<sf::Vector2f> ConvexShapeExtra::getGlobalPoints(const sf::ConvexShape &a) {
    std::vector<sf::Vector2f> result;

    const auto & pos = a.getPosition();

    auto numPoints = a.getPointCount();
    for (auto i = 0; i < numPoints; i++) {
        result.push_back(pos + a.getPoint(i));
    }
    return result;
}

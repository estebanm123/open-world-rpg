

#include "ConvexShapeExtra.h"
#include "MathExtra.h"

// How to get points w/ transformation?
std::vector<sf::Vector2f> ConvexShapeExtra::getGlobalPoints(const sf::ConvexShape &a) {
    std::vector<sf::Vector2f> result;

    const auto & transform = a.getTransform();

    auto numPoints = a.getPointCount();
    for (auto i = 0; i < numPoints; i++) {
        result.push_back(transform.transformPoint(a.getPoint(i)));
    }
    return result;
}

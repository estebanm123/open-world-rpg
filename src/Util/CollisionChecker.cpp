

#include "CollisionChecker.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>


#include "MathExtra.h"


bool CollisionChecker::intersect(const sf::CircleShape &circle, const sf::FloatRect &rect) {
    const auto origin = circle.getPosition();
    const auto closestX = clamp(origin.x, rect.left, rect.left + rect.width);
    const auto closestY = clamp(origin.y, rect.top, rect.top + rect.height);

    return distSquared(closestX, origin.x, closestY, origin.y) < (circle.getRadius() * circle.getRadius());
}

bool CollisionChecker::intersect(const sf::CircleShape &circle, const sf::RectangleShape &rectShape) {
    auto rect = convertToFloatRect(rectShape);
    const auto origin = circle.getPosition();
    const auto closestX = clamp(origin.x, rect.left, rect.left + rect.width);
    const auto closestY = clamp(origin.y, rect.top, rect.top + rect.height);

    return distSquared(closestX, origin.x, closestY, origin.y) < (circle.getRadius() * circle.getRadius());
}

bool CollisionChecker::intersect(const sf::RectangleShape &rectShape1, const sf::RectangleShape &rectShape2) {
    using namespace std;
    /*std::cout << "-intersect check-\n" << rectShape1.getPosition().x << ", " << rectShape1.getPosition().y << " :size " <<
        rectShape1.getSize().x << ", " << rectShape1.getSize().y << std::endl;
    std::cout << rectShape2.getPosition().x << ", " << rectShape2.getPosition().y << " :size " <<
        rectShape2.getSize().x << ", " << rectShape2.getSize().y << std::endl;*/
    //std::cout << endl;
//    auto rect1 = convertToFloatRect(rectShape1);
//    auto rect2 = convertToFloatRect(rectShape2);
    auto rect1 = rectShape1.getGlobalBounds();
    auto rect2 = rectShape2.getGlobalBounds();
    return rect1.intersects(rect2);

}


sf::FloatRect CollisionChecker::convertToFloatRect(const sf::RectangleShape &rect) {
    auto size = rect.getSize();
    auto pos = rect.getPosition();
    return {pos.x, pos.y, size.x, size.y};
}

bool CollisionChecker::intersect(const sf::ConvexShape &a, const sf::ConvexShape &b) {
    const auto aNumVertices = a.getPointCount();
    const auto bNumVertices = b.getPointCount();

    // is it ok to just use 1 edge instead of all ?
    for (auto i = 0; i < aNumVertices; i++) {
        auto cur = a.getPoint(i);
        auto next = a.getPoint((i + 1) % aNumVertices);
        auto edge = next - cur;
        sf::Vector2f axis {-edge.y, edge.x}; // normal

        auto aMaxProj = -std::numeric_limits<float>::infinity();
        auto aMinProj = std::numeric_limits<float>::infinity();
        auto bMaxProj = -std::numeric_limits<float>::infinity();
        auto bMinProj = std::numeric_limits<float>::infinity();

        for (auto v = a.getPoint(0); i < aNumVertices; v = a.getPoint(++i)) {
            auto proj = dotProduct(axis, v);
            if (proj < aMinProj) aMinProj = proj;
            if (proj > aMaxProj) aMaxProj = proj;
        }
        for (auto v = b.getPoint(0); i < bNumVertices; v = b.getPoint(++i)) {
            auto proj = dotProduct(axis, v);
            if (proj < bMinProj) bMinProj = proj;
            if (proj > bMaxProj) bMaxProj = proj;
        }

        if(aMaxProj < bMinProj || aMinProj > bMaxProj) {
            return true;
        }

    }
    return false;
}

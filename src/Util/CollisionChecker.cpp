

#include "CollisionChecker.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "MathExtra.h"
#include "Shapes/ConvexShapeExtra.h"

bool CollisionChecker::intersect(const sf::CircleShape &circle, const sf::FloatRect &rect) {
	const auto origin = circle.getPosition();
	const auto closestX = clamp(origin.x, rect.left, rect.left + rect.width);
	const auto closestY = clamp(origin.y, rect.top, rect.top + rect.height);

	return distSquared(closestX, origin.x, closestY, origin.y) < (circle.getRadius() * circle.getRadius());
}

bool CollisionChecker::intersect(const sf::ConvexShape &shapeA, const GlobalEdge &edgeB) {
	auto edges = ConvexShapeExtra::getGlobalEdges(shapeA);
	for (auto edgeA : edges) {
		// https://stackoverflow.com/questions/9043805/test-if-two-lines-intersect-javascript-function
		auto a = edgeA.vertexA.x, b = edgeA.vertexA.y, c = edgeA.vertexB.x, d = edgeA.vertexB.y;
		auto p = edgeB.vertexA.x, q = edgeB.vertexA.y, r = edgeB.vertexB.x, s = edgeB.vertexB.y;

		auto det = (c - a) * (s - q) - (r - p) * (d - b);
		if (det == 0) {
			return false;
		} else {
			auto lambda = ((s - q) * (r - a) + (p - r) * (s - b)) / det;
			auto gamma = ((b - d) * (r - a) + (c - a) * (s - b)) / det;
			if ((0 < lambda && lambda < 1) && (0 < gamma && gamma < 1)) {
				return true;
			}
		}
	}
	return false;
}

// SAT implementation
bool intersectUtil(const sf::ConvexShape &a, const sf::ConvexShape &b) {
	const auto aGlobalPoints = ConvexShapeExtra::getGlobalPoints(a);
	const auto bGlobalPoints = ConvexShapeExtra::getGlobalPoints(b);
	//    DebugPrint::separator();
	//    DebugPrint::print(a);
	//    DebugPrint::print(aGlobalPoints);
	////    DebugPrint::print(b);
	//    DebugPrint::print(bGlobalPoints);

	for (auto i = 0; i < aGlobalPoints.size(); i++) {
		auto cur = aGlobalPoints[i];
		auto next = aGlobalPoints[(i + 1) % aGlobalPoints.size()];
		auto edge = next - cur;
		sf::Vector2f axis{-edge.y, edge.x};	 // normal

		auto aMaxProj = -std::numeric_limits<float>::infinity();
		auto aMinProj = std::numeric_limits<float>::infinity();
		for (auto &point : aGlobalPoints) {
			auto proj = dotProduct(axis, point);
			aMinProj = std::min(proj, aMinProj);
			aMaxProj = std::max(proj, aMaxProj);
		}

		auto bMaxProj = -std::numeric_limits<float>::infinity();
		auto bMinProj = std::numeric_limits<float>::infinity();
		for (auto &point : bGlobalPoints) {
			auto proj = dotProduct(axis, point);
			bMinProj = std::min(proj, bMinProj);
			bMaxProj = std::max(proj, bMaxProj);
		}

		if (aMaxProj < bMinProj || aMinProj > bMaxProj) {
			return false;
		}
	}
	return true;
}

bool CollisionChecker::intersect(const sf::ConvexShape &a, const sf::ConvexShape &b) {
	return intersectUtil(a, b) && intersectUtil(b, a);
}

bool CollisionChecker::intersect(const SimpleCircle &circle, sf::Vector2f point) {
	auto xDist = std::abs(point.x - circle.center.x);
	auto yDist = std::abs(point.y - circle.center.y);
	return sqrtf(powf(xDist, 2) + powf(yDist, 2)) < circle.radius;
}

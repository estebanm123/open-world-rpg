

#include "ConvexShapeExtra.h"

std::vector<sf::Vector2f> ConvexShapeExtra::getGlobalPoints(const sf::ConvexShape &a) {
	std::vector<sf::Vector2f> result;

	const auto &transform = a.getTransform();

	auto numPoints = a.getPointCount();
	result.reserve(numPoints);
	for (auto i = 0; i < numPoints; i++) {
		result.push_back(transform.transformPoint(a.getPoint(i)));
	}
	return result;
}

std::vector<GlobalEdge> ConvexShapeExtra::getGlobalEdges(const sf::ConvexShape &a) {
	auto points = getGlobalPoints(a);
	auto numPoints = points.size();

	std::vector<GlobalEdge> edges;
	edges.reserve(points.size());

	for (auto i = 0; i < points.size(); i++) {
		edges.push_back(GlobalEdge{points[i], points[(i + 1) % numPoints]});
	}

	return edges;
}

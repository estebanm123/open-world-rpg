#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "Shapes/Edge.h"

constexpr float PI = 3.14159265f;
constexpr float MIN_PI = 3.14f;

template <typename T>
T toRadians(T degrees) {
	return degrees * PI / 180;
}

template <typename T>
T toDegrees(T radians) {
	return (radians * 180) / PI;
}

template <typename T>
T clamp(T val, T min, T max) {
	if (val >= max) return max;
	if (val <= min) return min;
	return min;
}

template <typename T>
T dist(T x1, T x2, T y1, T y2) {
	T distanceX = x1 - x2;
	T distanceY = y1 - y2;
	return sqrt((distanceX * distanceX) + (distanceY * distanceY));
}

template <typename T>
T distSquared(T x1, T x2, T y1, T y2) {
	T distanceX = x1 - x2;
	T distanceY = y1 - y2;
	return (distanceX * distanceX) + (distanceY * distanceY);
}

template <typename T>
T distSquared(sf::Vector2<T> p1, sf::Vector2<T> p2) {
	return distSquared(p1.x, p2.x, p1.y, p2.y);
}

template <typename T>
T dotProduct(sf::Vector2<T> v1, sf::Vector2<T> v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
T length(const sf::Vector2<T> &v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

template<typename T>
T lengthSquared(const sf::Vector2<T> &v) {
	return v.x * v.x + v.y * v.y;
}

template <typename T>
void normalize(sf::Vector2<T> &v) {
	v /= length(v);
}

template <typename T>
float angleBetweenTwoVectorsRad(sf::Vector2<T> v1, sf::Vector2<T> v2) {
	T dp = dotProduct(v1, v2);
	if (dp == 0) return PI / 2;
	return acos(dp / (length(v1) * length(v2)));
}

template <typename T>
static int fastFloor(T f) {
	return f >= 0 ? (int)f : (int)f - 1;
}

static GlobalEdge minDistPointToLineSquared(sf::Vector2f point, GlobalEdge line) {
	auto p = point;
	auto v = line.vertexA;
	auto w = line.vertexB;

	// Return minimum distance between line segment vw and point p
	auto diff = v - w;
	const float l2 = lengthSquared(sf::Vector2f{abs(diff.x), abs(diff.y)});	  // i.e. |w-v|^2 -  avoid a sqrt
	if (l2 == 0.0) return distSquared(p, v);  // v == w case
	// Consider the line extending the segment, parameterized as v + t (w - v).
	// We find projection of point p onto the line.
	// It falls where t = [(p-v) . (w-v)] / |w-v|^2
	// We clamp t from [0,1] to handle points outside the segment vw.
	const float t = max(0, min(1, dot(p - v, w - v) / l2));
	const sf::Vector2f projection = v + t * (w - v);  // Projection falls on the segment
	return distSquared(p, projection);
}

#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "Shapes/Edge.h"

constexpr float PI = 3.14159265f;
constexpr float MIN_PI = 3.14f;

template <typename T>
inline T toRadians(T degrees) {
	return degrees * PI / 180;
}

template <typename T>
inline T toDegrees(T radians) {
	return (radians * 180) / PI;
}

template <typename T>
inline T clamp(T val, T min, T max) {
	if (val >= max) return max;
	if (val <= min) return min;
	return min;
}

template <typename T>
inline T dist(T x1, T x2, T y1, T y2) {
	T distanceX = x1 - x2;
	T distanceY = y1 - y2;
	return sqrt((distanceX * distanceX) + (distanceY * distanceY));
}

template <typename T>
inline T distSquared(T x1, T x2, T y1, T y2) {
	T distanceX = x1 - x2;
	T distanceY = y1 - y2;
	return (distanceX * distanceX) + (distanceY * distanceY);
}

template <typename T>
inline T distSquared(sf::Vector2<T> p1, sf::Vector2<T> p2) {
	return distSquared(p1.x, p2.x, p1.y, p2.y);
}

template <typename T>
inline T dotProduct(sf::Vector2<T> v1, sf::Vector2<T> v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline T length(const sf::Vector2<T> &v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

template <typename T>
inline T lengthSquared(const sf::Vector2<T> &v) {
	return v.x * v.x + v.y * v.y;
}

template <typename T>
inline T lengthSquared(T x, T y) {
	return x * x + y * y;
}

template <typename T>
inline sf::Vector2<T> normalize(const sf::Vector2<T> &v) {
	return v / length(v);
}


template <typename T>
inline void normalizeRef(sf::Vector2<T> &v) {
	v /= length(v);
}

template <typename T>
inline void rotateRef(sf::Vector2<T> &v, float angleDegrees) {
	auto angleRadians = toRadians(angleDegrees);
	auto oldX = v.x;
	auto oldY = v.y;
	auto cosA = cos(angleRadians);
	auto sinA = sin(angleRadians);
	v.x = oldX * cosA - oldY * sinA;
	v.y = oldX * sinA + oldY * cosA;
}

template <typename T>
inline sf::Vector2<T> rotateVecAroundPoint(sf::Vector2<T> v,
										   sf::Vector2<T> point,
										   float angleDegrees) {
	auto angleRadians = toRadians(angleDegrees);
	float cs = cos(angleRadians);
	float sn = sin(angleRadians);

	float translated_x = v.x - point.x;
	float translated_y = v.y - point.y;

	float result_x = translated_x * cs - translated_y * sn;
	float result_y = translated_x * sn + translated_y * cs;

	result_x += point.x;
	result_y += point.y;
	return {result_x, result_y};
}

template <typename T>
inline bool isNegative(T num) {
	return num * -1 > num;
}

template <typename T>
inline bool isPositive(T num) {
	return !isNegative(num);
}

template <typename T>
inline float angleBetweenTwoVectorsRad(sf::Vector2<T> v1, sf::Vector2<T> v2) {
	T dp = dotProduct(v1, v2);
	if (dp == 0) return PI / 2;
	return acos(dp / (length(v1) * length(v2)));
}

template <typename T>
inline int fastFloor(T f) {
	return f >= 0 ? (int)f : (int)f - 1;
}

inline float minDistPointToLineSquared(sf::Vector2f point, GlobalEdge line) {
	auto p = point;
	auto v = line.vertexA;
	auto w = line.vertexB;

	// Return minimum distance between line segment vw and point p
	auto wv = v - w;
	const float l2 = lengthSquared(wv);

	// Consider the line extending the segment, parameterized as v + t (w - v).
	// We find projection of point p onto the line.
	// It falls where t = [(p-v) . (w-v)] / |w-v|^2
	// We clamp t from [0,1] to handle points outside the segment vw.
	const float t = std::max<float>(0, std::min<float>(1, dotProduct(p - v, w - v) / l2));
	const sf::Vector2f projection = v + t * (w - v);  // Projection falls on the segment
	return distSquared(p, projection);
}

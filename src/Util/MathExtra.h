#pragma once
#include "math.h"
#include <SFML/System/Vector2.hpp>

constexpr float PI = 3.14159265f;
constexpr float MIN_PI = 3.14f;


template <typename T>
T toRadians(T degrees)
{
    return degrees * PI / 180;
}

template <typename T>
T toDegrees(T radians)
{
    return (radians * 180) / PI;
}

template <typename T>
T clamp(T val, T min, T max)
{
    if (val >= max) return max;
    if (val <= min) return min;
    return min;
}

template <typename T>
T distSquared(T x1, T x2, T y1, T y2)
{
	T distanceX = x1 - x2;
	T distanceY = y1 - y2;
	return (distanceX * distanceX) + (distanceY * distanceY);
}

template <typename T>
T dotProduct(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
T length(sf::Vector2<T> v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

template <typename T>
void normalize(sf::Vector2<T>& v)
{
    v /= length(v);
}

template <typename T>
float angleBetweenTwoVectorsRad(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
    T dp = dotProduct(v1, v2);
    if (dp == 0) return PI / 2;
    return acos(dp / (length(v1) * length(v2)));
}
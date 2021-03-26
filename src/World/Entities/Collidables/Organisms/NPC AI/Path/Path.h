#pragma once

#include <deque>
#include <SFML/System.hpp>
#include <vector>

class Path {
public:
    typedef std::pair<sf::Vector2f, sf::Vector2f> Edge;
    typedef sf::Vector2f Point;

    const static sf::Vector2f EMPTY_POINT;
    const static Edge EMPTY_EDGE;

    Path(const std::vector<Point> & points);

    Edge getCurrentEdge() const;

    void enqueue(Point point);

    void advanceToNextPoint();

    void reset();

    static Edge makeEdge(const sf::Vector2f & first, const sf::Vector2f & second);

private:
    // Invariant: points.front() is first point of 'current edge'; points.back() is last point in path
    std::deque<Point> points;
};





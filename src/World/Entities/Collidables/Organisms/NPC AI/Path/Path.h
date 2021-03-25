#pragma once

#include <deque>
#include <SFML/System.hpp>
#include <vector>

// Dequeue of points.
// Useful for containing Npc points to travel to.
class Path {
public:
    typedef std::pair<sf::Vector2f, sf::Vector2f> Edge;
    typedef sf::Vector2f Point;

    const static sf::Vector2f EMPTY_POINT;
    const static Edge EMPTY_EDGE;

    Path(const std::vector<Point> & points);

    Point getCurrentPoint() const;

    Edge getCurrentEdge() const;

    void enqueue(Point point);

    Point removeCurrentPoint();

    void replaceCurrentPoint(Point point);

    void reset();

    static Edge makeEdge(const sf::Vector2f & first, const sf::Vector2f & second);

private:
    std::deque<Point> points;
};





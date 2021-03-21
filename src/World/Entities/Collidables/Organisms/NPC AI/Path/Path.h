#pragma once

#include <deque>
#include <SFML/System.hpp>

// Dequeue of points. Front is current point, back is last.
class Path {
public:
    typedef std::pair<sf::Vector2f, sf::Vector2f> Edge;
    typedef sf::Vector2f Point;

    const static sf::Vector2f EMPTY_POINT;
    const static Edge EMPTY_EDGE;

    Path(const std::vector<Point> & points);

    Point peekCurrentPoint() const;

    Edge getCurrentEdge() const;

    void push(Point point);

    void eraseCurrentPoint();

    void replaceCurrentPoint(Point point);

    void reset();

    static Edge makeEdge(const sf::Vector2f & first, const sf::Vector2f & second);

private:
    std::deque<Point> points;
};





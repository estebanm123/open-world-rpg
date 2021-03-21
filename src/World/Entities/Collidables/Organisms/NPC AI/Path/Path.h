#pragma once

#include <deque>
#include <SFML/System.hpp>

class PathManager;

class Path {
public:
    typedef std::pair<sf::Vector2f, sf::Vector2f> Edge;
    typedef sf::Vector2f Point;

    Path(PathManager * manager, int capacity = 5);

    Point peek() const;

    Edge getCurrentEdge() const;

    void push(Point point);

    void replaceCurrentPoint(Point point);

    static Edge makeEdge(const sf::Vector2f & first, const sf::Vector2f & second);

private:

    int capacity;
    std::deque<Point> points;
    Edge currentEdge;
    PathManager * manager;
};





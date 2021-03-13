#pragma once

#include <deque>
#include <SFML/System.hpp>

class PathManager;

class Path {
public:
    Path(PathManager * manager, int capacity = 5);

    typedef sf::Vector2f Point;
private:

    int capacity;
    std::deque<Point> points;
};





#pragma once

#include <deque>
#include <SFML/System.hpp>
#include <vector>

// Data structure storing an npc's last visited point and points intended to visit in the future
class NpcPath {
public:
    typedef std::pair<sf::Vector2f, sf::Vector2f> Edge;
    typedef sf::Vector2f Point;

    const static sf::Vector2f EMPTY_POINT;
    const static Edge EMPTY_EDGE;

    NpcPath(const std::vector<Point> & points = {});

    Edge getCurrentEdge() const;

    void enqueue(Point point);

    Point getNextPoint() const;

    // makes next point the last visited point
    void advanceToNextPoint();

    Point getLastVisitedPoint() const;

    bool noNextPoint() const;

    bool hasNextPoint() const;

    void reset();

    static Edge makeEdge(const sf::Vector2f & first, const sf::Vector2f & second);

private:
    // Invariant: points.front() is first point of 'current edge' ; the last point visited by npc
    // points.back() is last point in path
    std::deque<Point> points;
};





#pragma once

#include <deque>
#include <SFML/System.hpp>
#include <vector>

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

    void advanceToNextPoint();

    Point getLastVisitedPoint() const;

    bool noNextPoint() const;

    void reset();

    static Edge makeEdge(const sf::Vector2f & first, const sf::Vector2f & second);

private:
    // Invariant: points.front() is first point of 'current edge' ; the last point visited by npc
    // points.back() is last point in path
    std::deque<Point> points;
};





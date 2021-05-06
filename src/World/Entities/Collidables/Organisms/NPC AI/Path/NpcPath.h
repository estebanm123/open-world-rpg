#pragma once

#include <deque>
#include <SFML/System.hpp>
#include <vector>

class MoveableEntity;

// Data structure storing an npc's last visited point and points intended to visit in the future
class NpcPath {
public:
    typedef std::pair<sf::Vector2f, sf::Vector2f> Edge;
    typedef sf::Vector2f Point;

    const static sf::Vector2f EMPTY_POINT;
    const static Edge EMPTY_EDGE;

    NpcPath(const std::vector<Point> & points = {});

    void pushPointAndUpdateEntityDirection(MoveableEntity * entity, sf::Vector2f npcPos, Point newPoint);

    void enqueue(Point point);

    Point peekNextPoint() const;

    // makes popNextPoint point the last visited point
    void dequeueNextPoint();

    bool isEmpty() const;

    void reset();
private:
    // Invariant: points.front() is first point of 'current edge' ; the last point visited by npc
    // points.back() is last point in path
    std::deque<Point> points;

    friend class NpcDebug;
};

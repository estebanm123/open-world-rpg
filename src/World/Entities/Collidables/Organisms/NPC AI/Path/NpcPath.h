#pragma once

#include <deque>
#include <SFML/System.hpp>
#include <vector>

class MoveableEntity;

// Data structure storing an npc's last visited point and points intended to visit in the future
class NpcPath {
public:
    typedef std::pair<sf::Vector2f, sf::Vector2f> Edge;
//    typedef sf::Vector2f Point;

    struct Point {
        sf::Vector2f pos;
        bool isTemp = false; // temp points are disregarded as soon as another point is pushed in front of it
    };

    NpcPath(const std::vector<Point> & points = {});

    void pushPointAndUpdateEntityDirection(MoveableEntity *entity, sf::Vector2f npcPos, NpcPath::Point newPoint);

    void enqueue(sf::Vector2f point);

    void enqueue(Point point);

    Point peekNextPoint() const;

    void dequeueNextPoint();

    // dequeues any temp points before reaching a non-temp point. If there are no non-temp points, returns null.
    Point * getRealNextPoint();

    // Next point is real or temp
    void updateEntityDirectionWithNextPoint(MoveableEntity *entity, sf::Vector2f npcPos);

    bool isEmpty() const;

    // Removes all temp points until real next point and makes npc move to next point.
    // If no real next points, resets npc move direction.
    void reset(MoveableEntity * entity);
private:
    // Invariant: points.front() is first point of 'current edge' ; the last point visited by npc
    // points.back() is last point in path
    std::deque<Point> points;

    friend class NpcDebug;
};



#include <vector>
#include <cmath>
#include "NpcPath.h"
#include "../../../MoveableEntity.h"
#include "../../../../../../Util/MathExtra.h"

const sf::Vector2f NpcPath::EMPTY_POINT = {0, 0};

NpcPath::NpcPath(const std::vector<Point> &points) : points(points.begin(), points.end()) {}

void NpcPath::enqueue(NpcPath::Point point) {
    points.push_back(point);
}

void NpcPath::reset() {
    points.clear();
}

void NpcPath::dequeueNextPoint() {
    points.pop_front();
}

NpcPath::Point NpcPath::peekNextPoint() const {
    return points.front();
}

bool NpcPath::isEmpty() const {
    return points.empty();
}

void
NpcPath::pushPointAndUpdateEntityDirection(MoveableEntity *entity, sf::Vector2f npcPos, NpcPath::Point newPoint) {
    points.push_front(newPoint);

    auto newDir = newPoint - npcPos;
    entity->setMoveDirection(newDir);
    entity->setRotation(-toDegrees(atan2(newDir.x, newDir.y)));
}


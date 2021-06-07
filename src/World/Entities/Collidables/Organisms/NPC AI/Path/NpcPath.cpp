
#include "NpcPath.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "../../../../../../Util/MathExtra.h"
#include "../../../MoveableEntity.h"

NpcPath::NpcPath(const std::vector<Point> &points) : points(points.begin(), points.end()) {}

void NpcPath::enqueue(NpcPath::Point point) { points.push_back(point); }

void NpcPath::dequeueNextPoint() {
	if (!isEmpty()) {
		points.pop_front();
	}
}

NpcPath::Point NpcPath::peekNextPoint() const { return points.front(); }

bool NpcPath::isEmpty() const { return points.empty(); }

void NpcPath::pushPointAndUpdateEntityDirection(MoveableEntity *entity, sf::Vector2f npcPos, NpcPath::Point newPoint) {
	points.push_front(newPoint);
	updateEntityDirectionWithNextPoint(entity, npcPos);
}

NpcPath::Point *NpcPath::getRealNextPoint() {
	Point *nextPoint = nullptr;
	while (!points.empty()) {
		auto candidate = peekNextPoint();
		if (candidate.isTemp) {
			dequeueNextPoint();
		} else {
			nextPoint = &candidate;
			break;
		}
	}
	return nextPoint;
}

void NpcPath::updateEntityDirectionWithNextPoint(MoveableEntity *entity, sf::Vector2f npcPos) {
	if (isEmpty()) {
		entity->setMoveDirection({0, 0});
	} else {
		auto nextPoint = peekNextPoint();
		auto newDir = nextPoint.pos - npcPos;
		entity->setMoveDirection(newDir);
		entity->setRotation(-toDegrees(atan2(newDir.x, newDir.y)));
	}
}

void NpcPath::enqueue(sf::Vector2f point) { points.push_back(Point{point}); }

void NpcPath::reset(MoveableEntity *entity) {
	getRealNextPoint();
	updateEntityDirectionWithNextPoint(entity, entity->getPosition());
}

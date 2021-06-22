#pragma once

#include <iostream>

#include "../../../../../../Util/CollisionChecker.h"
#include "../../../../../../Util/MathExtra.h"
#include "../NpcAi.h"
#include "../Path/NpcPath.h"

// Handles NpcAi reactions to collisions with other entities; defines a set of default reactions
template <class OrganismOwner, class CollidingEntity>
class EntityReactor {
public:
	virtual void analyzeCollision(OrganismOwner *receivingEntity,
								  NpcAi<OrganismOwner> *ai,
								  CollidingEntity *otherEntity) = 0;
	// TODO: register activity observers, etc...
protected:
	// Attempts to change receivingEntity's path if otherEntity blocks it
	void handleBlockingEntity(OrganismOwner *receivingEntity,
							  NpcAi<OrganismOwner> *ai,
							  CollidingEntity *otherEntity) {
		if (!isEntityBlockingPath(receivingEntity, ai, otherEntity)) return;
		changePath(receivingEntity, ai, otherEntity);
	}

	virtual bool isEntityBlockingPath(OrganismOwner *receivingEntity,
									  NpcAi<OrganismOwner> *ai,
									  CollidingEntity *otherEntity) {
		auto receivingPos = receivingEntity->getPosition();
		auto otherPos = otherEntity->getPosition();
		auto otherSize = otherEntity->getSize();
		auto receivingSize = receivingEntity->getSize();
		auto maxOtherLength = std::max(otherSize.x, otherSize.y);
		auto maxReceivingLength = std::max(receivingSize.x, receivingSize.y);

		auto distToOther = dist(otherPos.x, receivingPos.x, otherPos.y, receivingPos.y);
		auto safeDistPastOther =
			distToOther + maxOtherLength +
			maxReceivingLength;	 // ray length; doesn't need to be precise as long as it reaches past the other entity
		auto receivingMoveDir = receivingEntity->getMoveDirection();
		auto translation = receivingMoveDir * safeDistPastOther * 40.f;

		auto centerRayEndPoint = receivingPos + translation;
		// receiving entity's edge points orthogonal to center ray
		auto edgePoint1 = receivingPos + sf::Vector2f{receivingMoveDir.y, -receivingMoveDir.x} *
											 maxReceivingLength / 2.f;
		auto edgeEndPoint1 = edgePoint1 + translation;
		auto edgePoint2 = receivingPos + sf::Vector2f{-receivingMoveDir.y, receivingMoveDir.x} *
											 maxReceivingLength / 2.f;
		auto edgeEndPoint2 = edgePoint2 + translation;
		// don't compute edgeEndPoints if move dir == 0,0

		const auto &bounds = otherEntity->getMainHitbox()->getBounds();
		return CollisionChecker::intersect(bounds, GlobalEdge{receivingPos, centerRayEndPoint}) ||
			   CollisionChecker::intersect(bounds, GlobalEdge{edgePoint1, edgeEndPoint1}) ||
			   CollisionChecker::intersect(bounds, GlobalEdge{edgePoint2, edgeEndPoint2});
		// todo: base on moveDirection instead of rotation angle
		// todo: try computing more than one ray? - first test out center ray; center may be sufficient
	}

private:
	void changePath(OrganismOwner *receivingEntity,
					NpcAi<OrganismOwner> *ai,
					CollidingEntity *otherEntity) {
		// todo: randomize direction of path change
		auto receivingPos = receivingEntity->getPosition();
		auto otherPos = otherEntity->getPosition();
		auto otherSize = otherEntity->getSize();
		auto receivingSize = receivingEntity->getSize();
		auto maxOtherLength = std::max(otherSize.x, otherSize.y);
		auto maxReceivingLength = std::max(receivingSize.x, receivingSize.y);

		auto vecBetweenEntities = sf::Vector2f{otherPos - receivingPos};
		normalize(vecBetweenEntities);
		auto newPointVec = sf::Vector2f{vecBetweenEntities.y, -vecBetweenEntities.x};
		auto length = maxOtherLength + maxReceivingLength / 2.f;
		auto newPoint = otherPos + newPointVec * length;

		auto &path = ai->getPath();
		path.pushPointAndUpdateEntityDirection(receivingEntity,
											   receivingPos,
											   NpcPath::Point{.pos = newPoint, .isTemp = true});
	}
};
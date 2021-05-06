#pragma once

#include "../NpcAi.h"
#include "../../../../../../Util/MathExtra.h"
#include "../../../../../../Util/CollisionChecker.h"

// Handles NpcAi reactions to collisions with other entities
template<class OrganismOwner, class CollidingEntity>
class EntityReactor {
public:
    virtual void
    analyzeCollision(OrganismOwner *receivingEntity, NpcAi<OrganismOwner> *ai, CollidingEntity *otherEntity) = 0;
    // TODO: register activity observers, etc...
protected:
    // Attempts to change receivingEntity's path if otherEntity blocks it
    void handleBlockingEntity(OrganismOwner *receivingEntity, NpcAi<OrganismOwner>* ai, CollidingEntity *otherEntity) {
        if (!isEntityBlockingPath(receivingEntity, ai, otherEntity)) return;
        changePath(receivingEntity, ai, otherEntity);
    }

    void changePath(OrganismOwner *receivingEntity, NpcAi<OrganismOwner> *ai, CollidingEntity *otherEntity) {
        // todo: randomize direction of path change
        auto receivingPos = receivingEntity->getPosition();
        auto otherPos = otherEntity->getPosition();
        auto otherSize = otherEntity->getSize();
        auto receivingSize = receivingEntity->getSize();

        auto newPoint = otherPos + otherSize / 2.f + receivingSize / 2.f;

        auto &path = ai->getPath();
        path.pushPointAndUpdateEntityDirection(receivingEntity, receivingPos, newPoint);
    }

    virtual bool
    isEntityBlockingPath(OrganismOwner *receivingEntity, NpcAi<OrganismOwner> * ai, CollidingEntity *otherEntity) {
        auto receivingPos = receivingEntity->getPosition();
        auto otherPos = otherEntity->getPosition();
        auto otherSize = otherEntity->getSize();
        auto receivingSize = receivingEntity->getSize();
        auto maxOtherLength = std::max(otherSize.x, otherSize.y);
        auto maxReceivingLength = std::max(receivingSize.x, receivingSize.y);

        auto distToOther = dist(otherPos.x, receivingPos.x, otherPos.y, receivingPos.y);
        auto safeDistPastOther = distToOther + maxOtherLength +
                                 maxReceivingLength; // ray length; doesn't need to be precise as long as it reaches past the other entity

        float angle = receivingEntity->getRotationAngle();
        auto centerRayEndPoint = receivingPos + safeDistPastOther * sf::Vector2f{std::sin(angle), std::cos(angle)};

        return CollisionChecker::intersect(otherEntity->getMainHitbox()->getBounds(),
                                           GlobalEdge{receivingPos, centerRayEndPoint});

        // todo: base on moveDirection instead of rotation angle
        // todo: try computing more than one ray? - first test out center ray; center may be sufficient

    }
};





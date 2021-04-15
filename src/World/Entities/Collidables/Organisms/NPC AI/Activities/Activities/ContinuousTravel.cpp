
#include "ContinuousTravel.h"
#include "../../../../../../../Util/CollisionChecker.h"


template<class Organism>
bool ContinuousTravel<Organism>::isNextPointReached(NpcPath *path, sf::Vector2f entityPos) const {
    return CollisionChecker::intersect(SimpleCircle{targetDistFromDestination, path->getNextPoint()}, entityPos);
}

template<class Organism>
void ContinuousTravel<Organism>::update(float dt) {
    auto npcEntity = this->ai->getEntity();
    auto npcPath = npcEntity->getPath();
    auto npcPos = npcEntity->getPosition();

    npcEntity->move(dt);

    if (isNextPointReached(npcPath, npcPos)) {
        if (npcPath.noNextPoint()) npcPath->enqueue(generateNextPoint());
        npcPath->advanceToNextPoint();
        // Todo change look direction
    }
}

template<class Organism>
ContinuousTravel<Organism>::ContinuousTravel(float targetDistFromDestination) : targetDistFromDestination(
        targetDistFromDestination) {}


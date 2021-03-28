
#include "ContinuousTravel.h"
#include "../../Path/NpcPath.h"
#include "../../../../../../../Util/CollisionChecker.h"


template<class Organism>
bool ContinuousTravel<Organism>::isNextPointReached(NpcPath * path, sf::Vector2f entityPos) const {
    return CollisionChecker::intersect(SimpleCircle{targetDistFromDestination, path->getNextPoint()}, entityPos);
}

template<class Organism>
void ContinuousTravel<Organism>::update(float dt) {
    auto npc = this->ai->getEntity();
    auto npcPath = npc->getPath();
    auto npcPos = npc->getPosition();

    if (isNextPointReached(npcPath, npcPos)) {
        if (npcPath.noNextPoint()) npcPath->enqueue(generateNextPoint());
        npcPath->advanceToNextPoint();

    }
}

template<class Organism>
ContinuousTravel<Organism>::ContinuousTravel(float targetDistFromDestination) : targetDistFromDestination(targetDistFromDestination) {}


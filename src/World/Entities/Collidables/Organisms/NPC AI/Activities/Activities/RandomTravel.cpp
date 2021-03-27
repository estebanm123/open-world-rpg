
#include "RandomTravel.h"
#include "../../Path/Path.h"
#include "../../../../../../../Util/CollisionChecker.h"


template<class Organism>
bool RandomTravel<Organism>::isNextPointReached(Path * path, sf::Vector2f entityPos) const {
    return CollisionChecker::intersect(SimpleCircle{maxRadius, path->getNextPoint()}, entityPos);
}

template<class Organism>
void RandomTravel<Organism>::update(float dt) {
    auto npc = this->ai->getEntity();
    auto npcPath = npc->getPath();
    auto npcPos = npc->getPosition();

    if (isNextPointReached(npcPath, npcPos)) {
        
    }
}

template<class Organism>
RandomTravel<Organism>::RandomTravel(float maxRadius) : maxRadius(maxRadius) {}


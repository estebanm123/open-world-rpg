

#include "NpcAi.h"

template<class Organism>
NpcAi<Organism>::NpcAi(Organism *entity) : entity(entity) {

}

template<class Organism>
void NpcAi<Organism>::analyzeCollision(const CollidableEntity &other) {

}

template<class Organism>
Organism *NpcAi<Organism>::getEntity() {
    return entity;
}

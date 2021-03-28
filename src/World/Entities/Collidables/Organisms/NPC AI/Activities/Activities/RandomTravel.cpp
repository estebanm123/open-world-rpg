
#include "RandomTravel.h"

template<class Organism>
RandomTravel<Organism>::RandomTravel(float targetDistFromDestination, const sf::Vector2f &initialPos,
                                     float maxRadiusOfTravel): ContinuousTravel<Organism>(targetDistFromDestination),
                                                               initialPos(initialPos),
                                                               maxRadiusOfTravel(maxRadiusOfTravel) {}

template<class Organism>
NpcPath::Point RandomTravel<Organism>::generateNextPoint() {
    float x = rand.getFloatInRange(initialPos.x - maxRadiusOfTravel, initialPos.x - maxRadiusOfTravel);
    float y = rand.getFloatInRange(initialPos.y - maxRadiusOfTravel, initialPos.y - maxRadiusOfTravel);
    return {x, y};
}


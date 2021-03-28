#pragma once


#include "ContinuousTravel.h"
#include "../../../../../../../Util/Random/Random.h"
#include <SFML/System.hpp>

template<class Organism>
class RandomTravel : public ContinuousTravel<Organism> {
protected:
    NpcPath::Point generateNextPoint() override;

public:
    RandomTravel(float targetDistFromDestination, const sf::Vector2f &initialPos, float maxRadiusOfTravel);

public:

private:
    const sf::Vector2f initialPos;
    float maxRadiusOfTravel;
    Random<float> rand;

};





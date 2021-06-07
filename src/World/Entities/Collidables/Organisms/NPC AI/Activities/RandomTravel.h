#pragma once

#include <SFML/System.hpp>

#include "../../../../../../Util/Random/Random.h"
#include "ContinuousTravel.h"

template <class Organism>
class RandomTravel : public ContinuousTravel<Organism> {
public:
	RandomTravel(float targetDistFromDestination, sf::Vector2f initialPos, float maxRadiusOfTravel, Idler idler = {})
		: ContinuousTravel<Organism>(targetDistFromDestination, Idler{idler}),
		  initialPos(initialPos),
		  maxRadiusOfTravel(maxRadiusOfTravel) {}

protected:
	NpcPath::Point generateNextPoint() override {
		float x = GlobalRand::rand.getFloatInRange(initialPos.x - maxRadiusOfTravel, initialPos.x + maxRadiusOfTravel);
		float y = GlobalRand::rand.getFloatInRange(initialPos.y - maxRadiusOfTravel, initialPos.y + maxRadiusOfTravel);
		return NpcPath::Point{sf::Vector2f{x, y}, true};
	}

private:
	const sf::Vector2f initialPos;
	float maxRadiusOfTravel;
};

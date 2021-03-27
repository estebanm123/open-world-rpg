#pragma once

#include "../BaseActivity.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System.hpp>
#include <utility>

class Path;

template<class Organism>
class RandomTravel : public BaseActivity<Organism> {
public:
    // maxRadius is radius from next point in NPC's path
    RandomTravel(float maxRadius);
    void update(float dt) override;

private:
    bool isNextPointReached(Path * path, sf::Vector2f entityPos) const;
    float maxRadius;
};





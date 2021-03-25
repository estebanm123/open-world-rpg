#pragma once

#include "../BaseActivity.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System.hpp>
#include <utility>

class Path;

template<class Organism>
class RandomTravel : public BaseActivity<Organism> {
public:
    RandomTravel(float maxRadius);
    void update(float dt) override;
private:

    bool isCurrentPointReached(Path * path, sf::Vector2f EntityPos) const;
    float maxRadius;
};





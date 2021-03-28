#pragma once

#include "../BaseActivity.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System.hpp>
#include <utility>
#include "../../Path/NpcPath.h"


template<class Organism>
class ContinuousTravel : public BaseActivity<Organism> {

    explicit ContinuousTravel(float targetDistFromDestination);
    void update(float dt) override;

protected:
    virtual NpcPath::Point generateNextPoint() = 0;
private:
    bool isNextPointReached(NpcPath * path, sf::Vector2f entityPos) const;
    float targetDistFromDestination;
};





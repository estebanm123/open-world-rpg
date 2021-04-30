#pragma once

#include "../BaseActivity.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System.hpp>
#include <utility>
#include "../../Path/NpcPath.h"
#include "../../../../../../../Util/CollisionChecker.h"


template<class Organism>
class ContinuousTravel : public BaseActivity<Organism> {
public:
    explicit ContinuousTravel(float targetDistFromDestination) : targetDistFromDestination(targetDistFromDestination) {}

    void initialize(NpcAi<Organism> *npcAi) override {
        BaseActivity<Organism>::initialize(npcAi);
    }

    void update(float dt) override {
        auto npcEntity = this->ai->getEntity();
        auto npcPath = this->ai->getPath();
        auto npcPos = npcEntity->getPosition();

        npcEntity->move(dt);

        if (npcPath.noNextPoint() || isNextPointReached(npcPath, npcPos)) {
            if (!npcPath.noNextPoint()) {
                npcPath.advanceToNextPoint();
            }
            npcPath.enqueue(generateNextPoint());
            npcEntity->setMoveDirection({1, 0});
            npcEntity->setLookDirection({1, 0});
        }
    }

protected:
    virtual NpcPath::Point generateNextPoint() = 0;

private:
    bool isNextPointReached(NpcPath &path, sf::Vector2f entityPos) const {
        return CollisionChecker::intersect(SimpleCircle{targetDistFromDestination, path.getNextPoint()}, entityPos);
    }

    float targetDistFromDestination;
};





#pragma once

#include "../BaseActivity.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System.hpp>
#include <utility>
#include <iostream>
#include "../../Path/NpcPath.h"
#include "../../../../../../../Util/CollisionChecker.h"
#include "../../../../../../../Util/MathExtra.h"
#include "../../AiDebug.h"


template<class Organism>
class ContinuousTravel : public BaseActivity<Organism> {
public:
    explicit ContinuousTravel(float targetDistFromDestination) : targetDistFromDestination(targetDistFromDestination) {}

    void initialize(NpcAi<Organism> *npcAi) override {
        BaseActivity<Organism>::initialize(npcAi);
    }

    void update(float dt) override {
        auto npcEntity = this->ai->getEntity();
        auto &npcPath = this->ai->getPath();
        auto npcPos = npcEntity->getPosition();

        npcEntity->move(dt);

        if (isNextPointReached(npcPath, npcPos)) {
            if (!npcPath.isEmpty()) {
                npcPath.popNextPoint();
            }

            auto generatedPoint = generateNextPoint();
            npcPath.enqueue(generatedPoint);

            auto newNpcDirection = computeMoveDirection(npcPath, npcPos);
            npcEntity->setMoveDirection(newNpcDirection);
            npcEntity->setRotation(-toDegrees(atan2(newNpcDirection.x, newNpcDirection.y)));
        }
    }

protected:
    virtual NpcPath::Point generateNextPoint() = 0;

private:
    sf::Vector2f computeMoveDirection(NpcPath &path, sf::Vector2f entityPos) {
        auto nextPoint = path.peekNextPoint();
        return nextPoint - entityPos;
    }

    bool isNextPointReached(NpcPath &path, sf::Vector2f entityPos) const {
        if (path.isEmpty()) return true;
        return CollisionChecker::intersect(SimpleCircle{targetDistFromDestination, path.peekNextPoint()}, entityPos);
    }

    float targetDistFromDestination;
};





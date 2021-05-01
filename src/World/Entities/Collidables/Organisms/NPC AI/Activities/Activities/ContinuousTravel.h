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

        if (npcPath.noTargetPoint() || isNextPointReached(npcPath, npcPos)) {
            std::cout << "npc   : " << npcPos.x << ", " << npcPos.y << std::endl;
            std::cout << "target: " << npcPath.getTargetPoint().x << ", " << npcPath.getTargetPoint().y << std::endl;

            AiDebug::printPath(npcPath);

            if (npcPath.hasTargetPoint()) {
                npcPath.advanceTargetPoint();
                AiDebug::printPath(npcPath, "Advancing point");
            }


            auto generatedPoint = generateNextPoint();
            npcPath.enqueue(generatedPoint);

            AiDebug::printPath(npcPath, "Enqueued point");

            auto newNpcDirection = computeMoveDirection(npcPath, npcPos);
            npcEntity->setMoveDirection(newNpcDirection);
            npcEntity->setRotation(-toDegrees(atan2(newNpcDirection.x, newNpcDirection.y)));
            std::cout << "moving to next point: " << npcPath.getTargetPoint().x << ", " << npcPath.getTargetPoint().y
                      << std::endl;
        }
    }

protected:
    virtual NpcPath::Point generateNextPoint() = 0;

private:
    sf::Vector2f computeMoveDirection(NpcPath &path, sf::Vector2f entityPos) {
        auto nextPoint = path.getTargetPoint();
        return nextPoint - entityPos;
    }

    bool isNextPointReached(NpcPath &path, sf::Vector2f entityPos) const {
        return CollisionChecker::intersect(SimpleCircle{targetDistFromDestination, path.getTargetPoint()}, entityPos);
    }

    float targetDistFromDestination;
};





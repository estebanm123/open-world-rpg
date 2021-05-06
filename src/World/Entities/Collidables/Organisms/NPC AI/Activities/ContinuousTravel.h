#pragma once

#include "BaseActivity.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System.hpp>
#include <utility>
#include <iostream>
#include "../Path/NpcPath.h"
#include "../../../MoveableEntity.h"
#include "../../../../../../Util/CollisionChecker.h"
#include "../../../../../../Util/MathExtra.h"
#include "../../../../../../Util/Random/Hash.h"
#include "../AiDebug.h"

// Simulates random idling for an entity
struct Idler {
    Idler(sf::Vector2f coords) : rand(mixCoords(coords.x, coords.y)) {}

    bool shouldEntityIdle() {
        if (!enabled) return false;
       auto idleScore = rand.getFloatInRange(0.f, 1.f);
        return idleScore <= idleProbability;
    }

    bool entityJustFinishedIdling() {
        if (!enabled) return false;
        bool retVal = justFinishedIdling;
        justFinishedIdling = false;
        return retVal;
    }

    void startIdling(MoveableEntity * entity) {
        if (!enabled) return;
        entity->setMoveDirection({0,0});

        idle = true;
        currentIdleDelay = rand.getFloatInRange(0.f, maxIdleSeconds);
        timer.restart();
    }

    bool isEntityIdle() {
        if (!enabled || !idle) return false;
        auto elapsedTime = timer.getElapsedTime().asSeconds();
        if (elapsedTime > currentIdleDelay) {
            justFinishedIdling = true;
            idle = false;
            return false;
        } else {
            return true;
        }
    }

private:
    bool enabled = true;
    bool idle = false;
    bool justFinishedIdling = false;
    sf::Clock timer{};
    float idleProbability = .8;
    int currentIdleDelay = 0;
    float maxIdleSeconds = 3.f;
    Random<> rand {};

};

// Only computes entity direction to next point once (after reaching dest)
// Optional random idles
template<class Organism>
class ContinuousTravel : public BaseActivity<Organism> {
public:
    explicit ContinuousTravel(float targetDistFromDestination, Idler idler = {}) :
            targetDistFromDestination(targetDistFromDestination),
            idler(idler) {}

    void initialize(NpcAi<Organism> *npcAi) override {
        BaseActivity<Organism>::initialize(npcAi);
    }

    void update(float dt) override {
        auto npcEntity = this->ai->getEntity();
        auto &npcPath = this->ai->getPath();
        auto npcPos = npcEntity->getPosition();

        if (idler.isEntityIdle()) {
            return;
        } else if (idler.entityJustFinishedIdling()) {
            moveTowardsNewPoint(npcPath, npcEntity, npcPos);
        } else {

            if (isNextPointReached(npcPath, npcPos)) {
                if (idler.shouldEntityIdle()) {
                    idler.startIdling(npcEntity);
                } else {
                    moveTowardsNewPoint(npcPath, npcEntity, npcPos);
                }
            }
        }
    }


protected:
    virtual NpcPath::Point generateNextPoint() = 0;

private:

    void moveTowardsNewPoint(NpcPath &npcPath, Organism *npcEntity, sf::Vector2f npcPos) {
        auto generatedPoint = generateNextPoint();
        npcPath.pushPointAndUpdateEntityDirection(npcEntity, npcPos, generatedPoint);
    }


    bool isNextPointReached(NpcPath &path, sf::Vector2f entityPos) const {
        if (path.isEmpty()) return true;
        return CollisionChecker::intersect(SimpleCircle{targetDistFromDestination, path.peekNextPoint()}, entityPos);
    }

    float targetDistFromDestination;
    Idler idler;
};

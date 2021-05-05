#pragma once


#include <memory>
#include "../../CollidableEntity.h"
#include "Activities/Activity Managers/ActivityManager.h"
#include "Path/NpcPath.h"
#include "AiDebug.h"

template<class Organism>
class NpcAi {
public:
    explicit NpcAi(std::unique_ptr<BaseActivity<Organism>> activities) : activities(std::move(activities)) {}

    void init(Organism *organism) {
        entity = organism;
        path.enqueue(entity->getPosition());
        this->activities->initialize(this);
    }

    void update(float dt) {
        activities->update(dt);
    }

    void analyzeCollision(CollidableEntity *other) {
        // todo forward
    };

    Organism *getEntity() {
        return entity;
    }

    SingleHitbox * getViewCone() {
        auto secondaryHitboxes = entity->getSecondaryHitboxes();
        if (!secondaryHitboxes) {
            throw std::runtime_error("Npc initialized without secondary hitboxes; should have at least a view cone");
        }
        auto & hitboxContainer = secondaryHitboxes->getHitboxes();
        if (hitboxContainer.empty()) {
            throw std::runtime_error("Npc initialized without secondary hitboxes; should have at least a view cone");
        }

        return hitboxContainer[0]->get();
    }

    NpcPath &getPath() {
        return path;
    }

private:
    Organism *entity;
    std::unique_ptr<BaseActivity<Organism>> activities;
    NpcPath path;
};





#pragma once


#include <memory>
#include "../../CollidableEntity.h"


//template<typename Organism>
//class ActivityManager<Organism>;

#include "Activities/Activity Managers/ActivityManager.h"

template<class Organism>
class NpcAi : EntityVisitor {
public:
    explicit NpcAi(std::unique_ptr<BaseActivity<Organism>> activities) : activities(
            std::move(activities)) {
    }

    void init(Organism *organism) {
        entity = organism;
    }

    void update(float dt) {
        activities->update(dt);
    }

    void analyzeCollision(CollidableEntity &other) {
        other.accept(this);
    };

    void visit(Beast *beast) {
        activities->visit(beast);
    }

    void visit(Humanoid *humanoid) {
        activities->visit(humanoid);
    }

    void visit(Prop *prop) {
        activities->visit(prop);
    }

    Organism *getEntity() {
        return entity;
    }

private:
    Organism *entity;
    std::unique_ptr<BaseActivity<Organism>> activities;
};





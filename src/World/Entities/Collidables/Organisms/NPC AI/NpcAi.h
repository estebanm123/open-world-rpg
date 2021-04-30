#pragma once


#include <memory>
#include "../../CollidableEntity.h"


//template<typename Organism>
//class ActivityManager<Organism>;

#include "Activities/Activity Managers/ActivityManager.h"
#include "Path/NpcPath.h"

template<class Organism>
class NpcAi : EntityVisitor {
public:
    explicit NpcAi(std::unique_ptr<BaseActivity<Organism>> activities) : activities(
            std::move(activities)) {
    }

    void init(Organism *organism) {
        entity = organism;
        path.enqueue(entity->getPosition());
        this->activities->initialize(this);
    }

    void update(float dt) {
        activities->update(dt);
    }

    void analyzeCollision(CollidableEntity &other) {
        other.accept(this);
    };

    void visit(Beast *beast) override {
        activities->visit(beast);
    }

    void visit(Humanoid *humanoid) override {
        activities->visit(humanoid);
    }

    void visit(Prop *prop) override {
        activities->visit(prop);
    }

    Organism *getEntity() {
        return entity;
    }

    NpcPath &getPath() {
        return path;
    }

private:
    Organism *entity;
    std::unique_ptr<BaseActivity<Organism>> activities;
    NpcPath path;
};





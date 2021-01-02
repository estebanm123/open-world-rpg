#pragma once

#include "../MoveableEntity.h"

class OrganismEntity : public MoveableEntity {
public:
    explicit OrganismEntity(const Hitbox &hitbox);
    // ctor?
//    virtual void sleep() = 0;
//    virtual void die() = 0;

    ~OrganismEntity() override = default;

protected:
};





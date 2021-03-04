#pragma once

#include "../MoveableEntity.h"

class OrganismEntity : public MoveableEntity {
public:

    explicit OrganismEntity(std::unique_ptr<Hitbox> hitbox);

//    virtual void sleep();
//    virtual void die();

    ~OrganismEntity() override = default;

protected:
};





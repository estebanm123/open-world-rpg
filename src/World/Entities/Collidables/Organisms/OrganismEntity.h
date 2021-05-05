#pragma once

#include "../MoveableEntity.h"

class OrganismEntity : public MoveableEntity {
public:

    explicit OrganismEntity(Config hitboxes);

//    virtual void sleep();
//    virtual void die();

    ~OrganismEntity() override = default;

protected:
};





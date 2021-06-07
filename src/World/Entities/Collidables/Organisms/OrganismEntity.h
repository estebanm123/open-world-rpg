#pragma once

#include "../MoveableEntity.h"

class OrganismEntity : public MoveableEntity {
public:
	explicit OrganismEntity(Config hitboxes, float initialSpeed);

	//    virtual void sleep();
	//    virtual void die();

	~OrganismEntity() override = default;

protected:
};

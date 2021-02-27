#pragma once


class CollidableEntity;

class MoveableEntity;

class CollisionPhysics {
public:
    virtual void applyCollisionPhysics(CollidableEntity * receivingEntity, MoveableEntity *movingEntity);
    virtual ~CollisionPhysics() = default;
};





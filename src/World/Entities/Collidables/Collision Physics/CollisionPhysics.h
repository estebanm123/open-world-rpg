#pragma once


class CollidableEntity;
class MoveableEntity;

class CollisionPhysics {
public:
    CollisionPhysics(CollidableEntity * entity);

    CollisionPhysics();

    virtual void applyCollisionPhysics(MoveableEntity * other);

    void setEntity(CollidableEntity * newEntity);
protected:
    CollidableEntity * entity;
};





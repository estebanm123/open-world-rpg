#pragma once


class CollidableEntity;

class MoveableEntity;

class CollisionPhysics {
public:
    explicit CollisionPhysics(CollidableEntity *entity);

    CollisionPhysics();

    virtual void applyCollisionPhysics(MoveableEntity *other);

    void setEntity(CollidableEntity *newEntity);

protected:
    CollidableEntity *entity;
};





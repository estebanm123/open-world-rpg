#pragma once


class CollidableEntity;

class MoveableEntity;

class Prop;

class CollisionPhysics {
public:
    // owner applies collision effects to
    virtual void applyPhysics(CollidableEntity * owner, MoveableEntity *movingEntity);
    virtual void applyPhysics(CollidableEntity * owner, Prop *prop);
    virtual ~CollisionPhysics() = default;
};





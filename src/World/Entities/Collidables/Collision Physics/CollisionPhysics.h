#pragma once

class CollidableEntity;

class MoveableEntity;

class Prop;

class CollisionPhysics {
public:
	virtual void applyPhysics(CollidableEntity *owner, MoveableEntity *movingEntity);
	virtual void applyPhysics(CollidableEntity *owner, Prop *prop);

	virtual bool isBlocking() const;
	virtual ~CollisionPhysics() = default;
};

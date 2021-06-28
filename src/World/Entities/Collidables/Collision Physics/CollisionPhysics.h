#pragma once

class CollidableEntity;

class MoveableEntity;

class Prop;

class CollisionPhysics {
public:
	CollisionPhysics(bool collisionAnalysisIsEnabledMoveables = false,
					 bool collisionAnalysisIsEnabledProps = false);

	virtual void applyPhysics(CollidableEntity *owner, MoveableEntity *movingEntity);
	virtual void applyPhysics(CollidableEntity *owner, Prop *prop);

	virtual bool isBlocking() const;
	virtual ~CollisionPhysics() = default;

private:
	bool collisionAnalysisIsEnabledMoveables;
	bool collisionAnalysisIsEnabledProps;
};

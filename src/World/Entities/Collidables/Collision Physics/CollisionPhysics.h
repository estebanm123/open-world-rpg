#pragma once

#include "../Hitbox/CollisionInfo.h"
class CollidableEntity;

class MoveableEntity;

class Prop;

class CollisionPhysics {
public:
	CollisionPhysics(bool collisionAnalysisIsEnabledMoveables = false,
					 bool collisionAnalysisIsEnabledProps = false);

	virtual void applyPhysics(CollisionInfo<MoveableEntity> &collisionInfo);
	virtual void applyPhysics(CollisionInfo<Prop> &collisionInfo);

	virtual bool isBlocking() const;
	virtual ~CollisionPhysics() = default;

private:
	bool collisionAnalysisIsEnabledMoveables;
	bool collisionAnalysisIsEnabledProps;
};

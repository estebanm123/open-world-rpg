#pragma once

class CollidableEntity;

class SingleHitbox;

template <class OtherEntityT, class ReceivingEntityT = CollidableEntity>
struct CollisionInfo {
	ReceivingEntityT* receivingEntity;
	OtherEntityT* otherEntity;
	SingleHitbox* receivingEntityHitbox;
	SingleHitbox* otherEntityHitbox;
	// todo: more details about actual collision?
};

#pragma once

#include "../../../../Util/CollisionChecker.h"
#include "../MoveableEntity.h"

struct EntityCollisionHandler {
	template <class CollidableA, class CollidableB>
	static void handleCollision(CollidableA *a, CollidableB *b) {
		auto aMainHitbox = a->getMainHitbox();
		auto bMainHitbox = b->getMainHitbox();

		if (CollisionChecker::intersect(aMainHitbox->getBounds(), bMainHitbox->getBounds())) {
			aMainHitbox->handleCollision(a, b);
			bMainHitbox->handleCollision(b, a);
			return;	 // short-circuit -> todo later: priority system?
		}

		handleSecondaryHitboxCollisions(a, b, bMainHitbox);
		handleSecondaryHitboxCollisions(b, a, aMainHitbox);
	}

	template <class CollidableA, class CollidableB>
	static bool areEntitiesColliding(CollidableA *a, CollidableB *b) {
		return CollisionChecker::intersect(b->getMainHitbox()->getBounds(),
										   a->getMainHitbox()->getBounds());
	}

private:
	template <class CollidableA, class CollidableB>
	static void handleSecondaryHitboxCollisions(CollidableA *a,
												CollidableB *b,
												SingleHitbox *bMainHitbox) {
		auto secondaryMultiHitbox = a->getSecondaryHitboxes();
		if (!secondaryMultiHitbox) return;
		auto &aSecondaryHitboxes = secondaryMultiHitbox->getHitboxes();
		for (auto &hitbox : aSecondaryHitboxes) {
			if (CollisionChecker::intersect(hitbox->getBounds(), bMainHitbox->getBounds())) {
				hitbox->handleCollision(a, b);
				return;	 // todo - maybe don't skip rest?
			}
		}
	}
};

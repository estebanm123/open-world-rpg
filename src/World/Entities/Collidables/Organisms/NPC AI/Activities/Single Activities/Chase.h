#pragma once

#include "../BaseActivity.h"

template <class OwnerOrganism, class OtherOrganism>
class Chase : public BaseActivity<OwnerOrganism> {
public:
	Chase(OtherOrganism* prey, float targetDistFromPrey = 100)
		: prey(prey),
		  targetDistFromPreySquared(targetDistFromPrey * targetDistFromPrey){};

	void update(float dt) {
		auto npcEntity = this->ai->getEntity();
		auto npcEntityPos = this->ai->getEntity()->getPosition();
		auto otherPos = prey->getPosition();

		auto newDir = npcEntityPos - otherPos;
		npcEntity->setMoveDirection(-newDir);
		npcEntity->setRotation(-toDegrees(atan2(newDir.x, newDir.y)));
	}

	bool isFinished() const override {
		auto npcEntityPos = this->ai->getEntity()->getPosition();
		auto otherPos = prey->getPosition();

		// todo: optimize? we don't need to calculate this every tick..
		auto distSqrd = distSquared(npcEntityPos.x, otherPos.x, npcEntityPos.y, otherPos.y);
		return distSqrd <= targetDistFromPreySquared;
	}

private:
	OtherOrganism* prey;
	float targetDistFromPreySquared;
};

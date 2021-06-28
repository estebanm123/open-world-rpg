#pragma once

#include "../../../../../../../Util/MathExtra.h"
#include "../BaseActivity.h"

template <class OwnerOrganism, class OtherOrganism>
class Flee : public BaseActivity<OwnerOrganism> {
public:
	Flee(OtherOrganism* predator, float safeDistFromPredator = 100)
		: predator(predator),
		  safeDistFromPredatorSquared(safeDistFromPredator * safeDistFromPredator){};

	void initialize(NpcAi<OwnerOrganism>* npcAi) override {
		BaseActivity<OwnerOrganism>::initialize(npcAi);
		auto& npcPath = this->ai->getPath();
		npcPath.reset(this->ai->getEntity());
	}

	void update(float dt) {
		auto npcEntity = this->ai->getEntity();
		auto npcEntityPos = this->ai->getEntity()->getPosition();
		auto otherPos = predator->getPosition();

		auto newDir = npcEntityPos - otherPos;
		npcEntity->setMoveDirection(newDir);
		npcEntity->setRotation(-toDegrees(atan2(newDir.x, newDir.y)));
	}

	bool isFinished() const override {
		auto npcEntityPos = this->ai->getEntity()->getPosition();
		auto otherPos = predator->getPosition();

		// todo: optimize? we don't need to calculate this every tick..
		auto distSqrd = distSquared(npcEntityPos.x, otherPos.x, npcEntityPos.y, otherPos.y);
		return distSqrd >= safeDistFromPredatorSquared;
	}

private:
	OtherOrganism* predator;
	float safeDistFromPredatorSquared;
};

#pragma once
#include "../AttackableCharacterAnim.h"

class BasicHeadAnim : public AttackableCharacterAnim
{
public:
	BasicHeadAnim();

    sf::IntRect resetAnimation() override;

private:
	std::shared_ptr<Animation> initializeMoveAnim() override;
	std::shared_ptr<Animation> initializeIdleAnim() override;
	std::shared_ptr<Animation> initializeFireAnim() override;
};

#pragma once
#include "Animation.h"

class NonRepeatingAnim : public Animation
{
public:
	NonRepeatingAnim(AnimationData data);
	const sf::IntRect& getFrame() override;
};

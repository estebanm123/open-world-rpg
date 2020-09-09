#pragma once
#include "Animation.h"

class RepeatingAnim : public Animation
{
public:
	explicit RepeatingAnim(AnimationData data);
	const sf::IntRect& getFrame() override;
};

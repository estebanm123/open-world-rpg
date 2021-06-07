#pragma once

#include "Animation.h"

class RepeatingAnim : public Animation {
public:
	explicit RepeatingAnim(Metadata data);

	const sf::IntRect &getFrameAndAdvanceAnim() override;

	const sf::IntRect &peekNextFrame() const override;
};

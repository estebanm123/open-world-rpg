#pragma once

#include "Animation.h"

class NonRepeatingAnim : public Animation {
public:
    explicit NonRepeatingAnim(AnimationData data);

    const sf::IntRect &getFrameAndAdvanceAnim() override;

    const sf::IntRect &peekNextFrame() const override;
};

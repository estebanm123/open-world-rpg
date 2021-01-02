#pragma once

#include "Animation.h"

class RepeatingAnim : public Animation {
public:
    explicit RepeatingAnim(AnimationData data);

    const sf::IntRect &getFrameAndAdvanceAnim() override;

    const sf::IntRect &peekNextFrame() const override;
};

#pragma once

#include <memory>

#include "../../Animation/Animation.h"


class AnimationPlayer : sf::NonCopyable {
public:
    virtual ~AnimationPlayer() = default;

    virtual sf::IntRect resetAnimation() = 0;

protected:
    std::shared_ptr<Animation> curAnim; // are there shared owners?

    virtual const sf::IntRect &playAnim(const std::shared_ptr<Animation> &anim);

    virtual const sf::IntRect &playAnim();
};

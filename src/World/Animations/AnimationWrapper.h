#pragma once

#include <memory>

#include "../../Util/Animation/Animation.h"


class AnimationWrapper : sf::NonCopyable {
public:
    virtual ~AnimationWrapper() = default;

    virtual sf::IntRect resetAnimation() = 0;

protected:
    std::shared_ptr<Animation> curAnim;

    virtual const sf::IntRect &playAnim(const std::shared_ptr<Animation> &anim);

    virtual const sf::IntRect &playAnim();
};

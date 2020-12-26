#pragma once

#include "../AnimationPlayer.h"

class CharacterAnim : public AnimationPlayer {
public:
    CharacterAnim(std::shared_ptr<Animation> moveAnim, std::shared_ptr<Animation> idleAnim);

    virtual const sf::IntRect &playMoveAnim();

    virtual const sf::IntRect &playIdleAnim();

protected:
    virtual std::shared_ptr<Animation> initializeMoveAnim() = 0;

    virtual std::shared_ptr<Animation> initializeIdleAnim() = 0;

    std::shared_ptr<Animation> moveAnim;
    std::shared_ptr<Animation> idleAnim;
};

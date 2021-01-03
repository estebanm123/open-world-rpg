#pragma once

#include "../AnimationPlayer.h"

class MoveableAnimationPlayer : public AnimationPlayer {
public:
    MoveableAnimationPlayer(EntitySprite &sprite, std::shared_ptr<Animation> moveAnim,
                            std::shared_ptr<Animation> idleAnim);

    virtual void playMoveAnim();

    virtual void playIdleAnim();

protected:
    virtual std::shared_ptr<Animation> initializeMoveAnim() = 0;

    virtual std::shared_ptr<Animation> initializeIdleAnim() = 0;

    std::shared_ptr<Animation> moveAnim;
    std::shared_ptr<Animation> idleAnim;
};





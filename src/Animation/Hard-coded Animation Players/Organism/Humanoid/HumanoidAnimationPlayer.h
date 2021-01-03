#pragma once

#include "../OrganismAnimationPlayer.h"

class HumanoidAnimationPlayer : public OrganismAnimationPlayer {
public:
    HumanoidAnimationPlayer(EntitySprite &sprite, std::shared_ptr<Animation> moveAnim,
                            std::shared_ptr<Animation> idleAnim, std::shared_ptr<Animation> useAnim);

    virtual void playUseAnim();

protected:
    virtual std::shared_ptr<Animation> initializeUseAnim() = 0;

    std::shared_ptr<Animation> useAnim;
};





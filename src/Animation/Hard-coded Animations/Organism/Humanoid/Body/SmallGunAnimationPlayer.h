#pragma once

#include "../HumanoidAnimationPlayer.h"

class SmallGunAnimationPlayer : public HumanoidAnimationPlayer {
public:
    SmallGunAnimationPlayer(EntitySprite &sprite);

    void resetAnimation() override;

private:
    std::shared_ptr<Animation> initializeMoveAnim() override;

    std::shared_ptr<Animation> initializeIdleAnim() override;

    std::shared_ptr<Animation> initializeUseAnim() override;
};





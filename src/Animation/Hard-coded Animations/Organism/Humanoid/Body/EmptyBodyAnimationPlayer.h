#pragma once

#include "../HumanoidAnimationPlayer.h"

class EmptyBodyAnimationPlayer : public HumanoidAnimationPlayer {
public:
    EmptyBodyAnimationPlayer(EntitySprite &sprite);

    void resetAnimation() override;

private:
    std::shared_ptr<Animation> initializeMoveAnim() override;

    std::shared_ptr<Animation> initializeIdleAnim() override;

    std::shared_ptr<Animation> initializeUseAnim() override;
};








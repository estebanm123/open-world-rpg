#pragma once

#include "../HumanoidAnimationPlayer.h"
#include "../../../../../World/Entities/RegSprite.h"

class EmptyBodyAnimationPlayer : public HumanoidAnimationPlayer {
public:
    EmptyBodyAnimationPlayer(RegSprite *sprite);

    void resetAnimation() override;

private:
    std::shared_ptr<Animation> initializeMoveAnim() override;

    std::shared_ptr<Animation> initializeIdleAnim() override;

    std::shared_ptr<Animation> initializeUseAnim() override;
};










#include "EmptyBodyAnimationPlayer.h"
#include "../../../../../Animation/RepeatingAnim.h"

using namespace animConstants;

EmptyBodyAnimationPlayer::EmptyBodyAnimationPlayer(EntitySprite &sprite) : HumanoidAnimationPlayer(sprite,
                                                                                                   EmptyBodyAnimationPlayer::initializeMoveAnim(),
                                                                                                   EmptyBodyAnimationPlayer::initializeIdleAnim(),
                                                                                                   EmptyBodyAnimationPlayer::initializeUseAnim()) {

}

void EmptyBodyAnimationPlayer::resetAnimation() {
    curAnim = idleAnim;
    curAnim->resetAnimation();
}

std::shared_ptr<Animation> EmptyBodyAnimationPlayer::initializeMoveAnim() {
    auto row = 0;
    auto frameStart = 0;
    auto frameEnd = 2;
    auto priority = 0;
    const std::vector<int> inversionFrames = {2, 5};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, priority,
                                  BODY_MOVE_FRAME_DELAY, inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> EmptyBodyAnimationPlayer::initializeIdleAnim() {
    auto row = 0;
    auto frameStart = 6;
    auto frameEnd = 8;
    auto priority = 0;
    const std::vector<int> inversionFrames = {8};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, priority,
                                  (BODY_IDLE_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> EmptyBodyAnimationPlayer::initializeUseAnim() {
    return nullptr;
}

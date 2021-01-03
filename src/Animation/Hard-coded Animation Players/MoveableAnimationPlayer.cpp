

#include "MoveableAnimationPlayer.h"

MoveableAnimationPlayer::MoveableAnimationPlayer(EntitySprite &sprite, std::shared_ptr<Animation> moveAnim,
                                                 std::shared_ptr<Animation> idleAnim) : AnimationPlayer(sprite),
                                                                                        moveAnim(std::move(moveAnim)),
                                                                                        idleAnim(std::move(idleAnim)) {
}

void MoveableAnimationPlayer::playMoveAnim() {
    return playAnim(moveAnim);
}

void MoveableAnimationPlayer::playIdleAnim() {
    return playAnim(idleAnim);
}

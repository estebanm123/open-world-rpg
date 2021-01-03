#include "AnimationPlayer.h"

void AnimationPlayer::playAnim(const std::shared_ptr<Animation> &anim) {
    if (!curAnim || curAnim->peekNextFrame() == animConstants::EMPTY_FRAME ||
        curAnim->getPriority() <= anim->getPriority()) {
        curAnim = anim;
    }
    return playCurrentAnim();
}

void AnimationPlayer::playCurrentAnim() {
    const auto &nextFrame = curAnim->getFrameAndAdvanceAnim();
    if (sprite.getTextureRect() != nextFrame) {
        sprite.setTextureRect(curAnim->getFrameAndAdvanceAnim());
    }
}

AnimationPlayer::AnimationPlayer(EntitySprite &sprite) : sprite(sprite) {
}

void AnimationPlayer::resetAnimation() {
    if (curAnim) curAnim->resetAnimation();
}

void AnimationPlayer::setCurrentAnim(std::shared_ptr<Animation> anim) {
    curAnim = std::move(anim);
}


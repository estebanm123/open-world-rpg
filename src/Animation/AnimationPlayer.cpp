#include "AnimationPlayer.h"

#include <utility>

AnimationPlayer::AnimationPlayer(EntitySprite *sprite, std::shared_ptr<Animation> anim) : sprite(sprite), curAnim(std::move(anim)) {}

AnimationPlayer::AnimationPlayer() : sprite(nullptr), curAnim(nullptr) {

}


void AnimationPlayer::playAnim(const std::shared_ptr<Animation> &anim) {
    if (anim == nullptr) {
        return;
    }

    if ((!curAnim || curAnim->peekNextFrame() == animConstants::EMPTY_FRAME ||
        curAnim->getPriority() <= anim->getPriority())) {
        curAnim = anim;
    }
    return playCurrentAnim();
}

void AnimationPlayer::playCurrentAnim() {
    const auto &nextFrame = curAnim->getFrameAndAdvanceAnim();
    if (sprite->getTextureRect() != nextFrame) {
        sprite->setTextureRect(curAnim->getFrameAndAdvanceAnim());
    }
}

void AnimationPlayer::resetAnimation() {
    if (curAnim) {
        curAnim->resetAnimation();
    }
}

void AnimationPlayer::setCurrentAnim(std::shared_ptr<Animation> anim) {
    curAnim = std::move(anim);
}

bool AnimationPlayer::hasCurrentAnim() const {
    return !(curAnim == nullptr);
}

void AnimationPlayer::setSprite(EntitySprite* newSprite) {
    sprite = newSprite;
}



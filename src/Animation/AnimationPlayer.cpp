#include "AnimationPlayer.h"
#include "Actions.h"

using namespace animConstants;

AnimationPlayer::AnimationPlayer(std::unordered_map<Action const *, std::unique_ptr<Animation>> anims,
                                 Action const *initialAction) : anims(std::move(anims)), curAnim(nullptr) {
    if (initialAction != nullptr) {
        curAnim = getAnim(initialAction);
    }
}

AnimationPlayer::AnimationPlayer(std::unique_ptr<Animation> defaultAnim) {
    curAnim = defaultAnim.get();
    setDefaultAnim(std::move(defaultAnim));
}

const sf::IntRect &AnimationPlayer::playAnim(Action const *action) {
    auto anim = getAnim(action);
    if (!anim) return EMPTY_FRAME;

    if (!curAnim || curAnim->peekNextFrame() == animConstants::EMPTY_FRAME ||
                 curAnim->getPriority() <= anim->getPriority()) {
        curAnim = anim;
    }

    return playCurrentAnim();
}

const sf::IntRect &AnimationPlayer::playCurrentAnim() {
    if (!curAnim) return EMPTY_FRAME;
    const auto &nextFrame = curAnim->getFrameAndAdvanceAnim();
    return nextFrame;
}

void AnimationPlayer::resetAnimation() {
    if (curAnim) {
        curAnim->resetAnimation();
    }
}

bool AnimationPlayer::hasCurrentAnim() const {
    return curAnim != nullptr;
}

Animation *AnimationPlayer::getAnim(Action const *action) {
    if (anims.find(action) == anims.end()) return nullptr;
    return anims.at(action).get();
}

void AnimationPlayer::setDefaultAnim(std::unique_ptr<Animation> anim) {
    // todo: verify safety
    curAnim = anim.get();
    anims.insert({&Actions::Default, std::move(anim)});
}

bool AnimationPlayer::noAnimCurrentlyPlaying() {
    return curAnim == nullptr || curAnim->peekNextFrame() == EMPTY_FRAME;
}


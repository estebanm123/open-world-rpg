#include "AnimationPlayer.h"

const sf::IntRect &AnimationPlayer::playAnim(const std::shared_ptr<Animation> &anim) {
    curAnim = anim;
    return playAnim();
}

const sf::IntRect &AnimationPlayer::playAnim() {
    return curAnim->getFrame();
}

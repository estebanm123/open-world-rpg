#include "CharacterAnim.h"

CharacterAnim::CharacterAnim(std::shared_ptr<Animation> moveAnim, std::shared_ptr<Animation> idleAnim)
        : moveAnim(std::move(moveAnim)), idleAnim(std::move(idleAnim)) {
}

const sf::IntRect &CharacterAnim::playMoveAnim() {
    return playAnim(moveAnim);
}

const sf::IntRect &CharacterAnim::playIdleAnim() {
    return playAnim(idleAnim);
}

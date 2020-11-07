#include "PlayableHumanoidSprite.h"

#include "../../Resource Managers/ResourceHolder.h"
#include "../Animations/CharacterAnims/BodyAnims/EmptyHandedBodyAnim.h"

PlayableHumanoidSprite::PlayableHumanoidSprite(const std::string &bodySheet, const std::string &headSheet,
                                               const std::string &legsSheet)
        : bodyAnim(new EmptyHandedBodyAnim()), legAnim(new PlayerLegsAnim()), headAnim(new BasicHeadAnim()),
          lockAnim(false) {
    using namespace animConstants;
    body.setOrigin(BASE_FRAME_WIDTH / 2.f, BASE_FRAME_HEIGHT / 3.f);
    head.setOrigin(BASE_FRAME_WIDTH / 2.f, BASE_FRAME_HEIGHT / 1.8f);
    legs.setOrigin(BASE_FRAME_WIDTH / 2.f, BASE_FRAME_HEIGHT / 2.f);

    initializeHitBox();
    initializeTextures(bodySheet, headSheet, legsSheet);
    resetMoveAnim();
}

void PlayableHumanoidSprite::renderBy(sf::RenderTarget &renderer) const {
    renderer.draw(legs);
    renderer.draw(body);
    renderer.draw(head);
}

void PlayableHumanoidSprite::setPosition(sf::Vector2f pos) {
    body.setPosition(pos);
    head.setPosition(pos);
    legs.setPosition(pos);
    hitBox.setPosition(pos);
}

// returns position of front of head in world coordinates
sf::Vector2f PlayableHumanoidSprite::getPosition() const {
    return body.getPosition();
}

void PlayableHumanoidSprite::setRotation(float angle) {
    body.setRotation(angle);
    head.setRotation(angle);
    hitBox.setRotation(angle);
}

// resets to bodyAnim to EmptyHandedBodyAnim
void PlayableHumanoidSprite::swapBody() {
    bodyAnim = bodyAnimFactory.generateEmptyHanded();
}

bool PlayableHumanoidSprite::isLocked() const {
    return lockAnim;
}

void PlayableHumanoidSprite::swapBody(const std::shared_ptr<Weapon> &weapon) {
    bodyAnim = weapon->accept(bodyAnimFactory);
}


void PlayableHumanoidSprite::move(sf::Vector2f offset) {
    legs.move(offset);
    body.move(offset);
    head.move(offset);
    hitBox.move(offset);
}

void PlayableHumanoidSprite::playIdleAnim() {
    // head idle anim
    if (!lockAnim) {
        body.setTextureRect(bodyAnim->playIdleAnim());
    }
}

// resets legs animation and rest of sprite to idle (absent)
// if body/ head is playing a fixed-length animation (is locked),only reset legs
void PlayableHumanoidSprite::resetMoveAnim() {
    if (!lockAnim) {
        resetBody();
        resetHead();
    } else {
        auto bounds = bodyAnim->playFireAnim();
        if (bounds != animConstants::EMPTY_FRAME) {
            body.setTextureRect(bounds);
            //head.setTextureRect(headAnim->playMoveAnim()); // to change
        } else {
            lockAnim = false;
        }
    }
    resetLegs();

}

void PlayableHumanoidSprite::playVerticalAnim() {
    playMoveAnimOnSprite(legAnim->playVerticalAnim());
}

void PlayableHumanoidSprite::playHorizontalAnim() {
    playMoveAnimOnSprite(legAnim->playHorizontalAnim());
}

void PlayableHumanoidSprite::playTopLeftDiagonalAnim() {
    playMoveAnimOnSprite(legAnim->playTopLeftDiagonalAnim());
}

void PlayableHumanoidSprite::playTopRightDiagonalAnim() {
    playMoveAnimOnSprite(legAnim->playTopRightDiagonalAnim());

}

const sf::RectangleShape &PlayableHumanoidSprite::getHitBox() const {
    return hitBox;
}

void PlayableHumanoidSprite::enableLock() {
    lockAnim = true;
}

void PlayableHumanoidSprite::resetLegs() {
    legs.setTextureRect(legAnim->resetAnimation());
}

void PlayableHumanoidSprite::resetHead() {
    head.setTextureRect(headAnim->resetAnimation());
}

void PlayableHumanoidSprite::resetBody() {
    body.setTextureRect(bodyAnim->resetAnimation());
}

// if move anim is locked, plays fire anim, until the anim has ended
// else plays regular body/ head move anim
// legs are updated regardless
void PlayableHumanoidSprite::playMoveAnimOnSprite(const sf::IntRect &legsBound) {
    if (lockAnim) {
        auto bounds = bodyAnim->playFireAnim();
        if (bounds != animConstants::EMPTY_FRAME) {
            body.setTextureRect(bounds);
            head.setTextureRect(headAnim->playMoveAnim()); // change to a specific fire anim
        } else {
            lockAnim = false;
        }
    } else {
        body.setTextureRect(bodyAnim->playMoveAnim());
        head.setTextureRect(headAnim->playMoveAnim());
    }
    legs.setTextureRect(legsBound);
}

void PlayableHumanoidSprite::initializeTextures(const std::string &bodySheet, const std::string &headSheet,
                                                const std::string &legsSheet) {
    legs.setTexture(ResourceHolder::get().textures.get(legsSheet));
    body.setTexture(ResourceHolder::get().textures.get(bodySheet));
    head.setTexture(ResourceHolder::get().textures.get(headSheet));
}

void PlayableHumanoidSprite::initializeHitBox() {
    sf::Vector2f hitBoxSize = {animConstants::BASE_FRAME_WIDTH / 2.f, animConstants::BASE_FRAME_HEIGHT / 3.f};
    hitBox.setOrigin(hitBoxSize / 2.f);
    hitBox.setSize(hitBoxSize);
    auto pos = body.getPosition();
    hitBox.setPosition(pos.x, pos.y);
}

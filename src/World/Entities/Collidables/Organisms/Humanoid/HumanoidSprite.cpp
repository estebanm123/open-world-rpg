

#include "HumanoidSprite.h"
#include "../../../../../Animation/Animation.h"
#include "../../../../../Animation/Hard-coded Animation Players/Organism/Humanoid/Head/BasicHeadAnimationPlayer.h"
#include "../../../../../Animation/Hard-coded Animation Players/Organism/Humanoid/Body/EmptyBodyAnimationPlayer.h"

using namespace animConstants;

HumanoidSprite::HumanoidSprite(const std::string &spriteSheetBody, const std::string &spriteSheetHead,
                               const sf::Vector2f &pos) : head(spriteSheetHead, pos,
                                                               {BASE_FRAME_WIDTH / 2.f,
                                                                BASE_FRAME_HEIGHT /
                                                                1.8f}),
                                                          body(spriteSheetBody, pos,
                                                               {BASE_FRAME_WIDTH / 2.f,
                                                                BASE_FRAME_HEIGHT /
                                                                3.f}),
                                                          headAnimation(
                                                                  std::make_unique<BasicHeadAnimationPlayer>(&head)),
                                                          bodyAnimation(
                                                                  std::make_unique<EmptyBodyAnimationPlayer>(&body)) {

    head.setTextureRect({0, 0, BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT});

}

void HumanoidSprite::setTexture(const sf::Texture &texture) {
    head.setTexture(texture);
    body.setTexture(texture);
}

const sf::IntRect &HumanoidSprite::getTextureRect() const {
    return body.getTextureRect();
}

void HumanoidSprite::setTextureRect(const sf::IntRect &rectangle) {
    body.setTextureRect(rectangle);
}

const sf::Vector2f &HumanoidSprite::getPosition() const {
    body.getPosition();
}

void HumanoidSprite::setPosition(const sf::Vector2f &pos) {
    head.setPosition(pos);
    body.setPosition(pos);
}

float HumanoidSprite::getRotation() const {
    return body.getRotation();
}

void HumanoidSprite::setRotation(float angle) {
    body.setRotation(angle);
    head.setRotation(angle);
}

void HumanoidSprite::renderBy(sf::RenderTarget &renderer) {
    body.renderBy(renderer);
    head.renderBy(renderer);
}

void HumanoidSprite::move(const sf::Vector2f &offset) {
    body.move(offset);
    head.move(offset);
}

void HumanoidSprite::playIdleAnim() {
    bodyAnimation->playIdleAnim();
    headAnimation->resetAnimation();
}

void HumanoidSprite::playMoveAnim() {
    headAnimation->playMoveAnim();
    bodyAnimation->playMoveAnim();
}

void HumanoidSprite::playUseAnim() {
    bodyAnimation->playUseAnim();
    headAnimation->playMoveAnim();
}






#include "Humanoid.h"
#include "../../../../../Animation/Hard-coded Animations/HumanoidAnimInitializer.h"
#include "../../../Sprites/ShadowedSpriteReg.h"
#include "../../../../../Animation/AnimationPlayer.h"
#include "../../Hitbox/SingleHitbox.h"

Humanoid::Humanoid(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
                   const std::string &spriteSheetHead) : OrganismEntity(std::make_unique<SingleHitbox>(sf::FloatRect {globalPosition.x, globalPosition.y, BASE_FRAME_WIDTH / 2.f, BASE_FRAME_HEIGHT / 2.f})),
                                                         sprite(initializeSprites(globalPosition, spriteSheetBody,
                                                                                  spriteSheetHead)),
                                                         isPickingUp(false) {
}


EntitySprite &Humanoid::getSprite() {
    return sprite;
}

void Humanoid::dropCurrentItem() {

}

void Humanoid::useCurrentItem() {

}

void Humanoid::setPickingUp(bool pickingUp) {
    isPickingUp = pickingUp;
}

bool Humanoid::pickingUp() const {
    return isPickingUp;
}

void Humanoid::revertLastMove(bool x, bool y) {
    MoveableEntity::revertLastMove(x, y);
}

void Humanoid::renderBy(sf::RenderTarget &renderer) {
    // move/group this animation handling to organism and take a AnimPlayer proxy?

    // could be eating, sleeping, using etc.. -> maybe we have a current action field?
    // at least not for the movement cause it can be manipulated after player update


    if (hasMoved()) {
        sprite.playAnim(&MoveableActions::Move);
        //
    } else {
        sprite.playAnim(&MoveableActions::Idle);
    }
    CollidableEntity::renderBy(renderer);
}

std::vector<std::unique_ptr<EntitySprite>>
Humanoid::initializeSprites(const sf::Vector2f &pos, const std::string &spriteSheetBody,
                            const std::string &spriteSheetHead) {
    using namespace animConstants;
    std::vector<std::unique_ptr<EntitySprite>> sprites;
    sprites.push_back(
            std::make_unique<ShadowedSpriteReg>(ShadowedSpriteReg{spriteSheetBody, pos, {BASE_FRAME_WIDTH / 2.f,
                                                                                         BASE_FRAME_HEIGHT /
                                                                                         3.f},
                                                                  std::move(
                                                                          HumanoidAnimInitializer::initializeEmptyBody())}));
    sprites.push_back(std::make_unique<SpriteReg>(SpriteReg::Config{spriteSheetHead, pos, {BASE_FRAME_WIDTH / 2.f,
                                                                                           BASE_FRAME_HEIGHT /
                                                                                           1.8f},
                                                                    std::move(
                                                                            HumanoidAnimInitializer::initializeEmptyHead()),
                                                                    {0, 0, BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT}}));
    return sprites;
}

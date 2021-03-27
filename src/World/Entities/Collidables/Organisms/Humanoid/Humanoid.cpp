#include "Humanoid.h"
#include "../../../../../Animation/Hard-coded Animations/HumanoidAnimInitializer.h"
#include "../../../Sprites/ShadowedSpriteReg.h"
#include "../../Hitbox/SingleHitbox.h"
#include "../../../EntityVisitor/EntityVisitor.h"


Humanoid::Humanoid(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
                   const std::string &spriteSheetHead) : OrganismEntity(std::make_unique<SingleHitbox>(sf::FloatRect {globalPosition.x, globalPosition.y, BASE_FRAME_WIDTH / 2.f, BASE_FRAME_HEIGHT / 2.f})),
                                                         sprite(initializeSprites(globalPosition, spriteSheetBody,
                                                                                  spriteSheetHead)),
                                                         isPickingUp(false) {
}


EntitySprite &Humanoid::getSprite() {
    return sprite;
}

void Humanoid::revertLastMove(bool x, bool y) {
    MoveableEntity::revertLastMove(x, y);
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

void Humanoid::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

void Humanoid::attemptPickup() {
    this->setCurrentAction(&HumanoidActions::Touch);
    // todo: Deploy a temporary hitbox for the hand/reach
}

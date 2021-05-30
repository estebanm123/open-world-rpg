#include "Humanoid.h"
#include "../../../../../Animation/Hard-coded Animations/HumanoidAnimInitializer.h"
#include "../../../Sprites/ShadowedSpriteReg.h"
#include "../../Hitbox/SingleHitbox.h"
#include "../../../EntityVisitor/EntityVisitor.h"
#include "../../Collision Physics/BlockingPhysics.h"
#include "../../../Surface Effects/FootprintGenerator.h"

Humanoid::Humanoid(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
                   const std::string &spriteSheetHead, float initialSpeed) :
        OrganismEntity(
                CollidableEntity::Config{.mainHitbox =  std::make_unique<SingleHitbox>(
                        sf::FloatRect{globalPosition.x, globalPosition.y, BASE_FRAME_WIDTH / 2.f,
                                      BASE_FRAME_HEIGHT / 3.f}, 0,
                        std::make_unique<BlockingPhysics>())}, initialSpeed),
        sprite(initializeSprites(globalPosition, spriteSheetBody,
                                 spriteSheetHead)),
        isPickingUp(false) {
    initializeFootprintGenerator();
}


EntitySprite &Humanoid::getSprite() {
    return sprite;
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

void Humanoid::initializeFootprintGenerator() {
    auto pos = getPosition();
    auto size = getSize();
    auto spriteConfig = SpriteReg::CopyableConfig{.spriteSheet= "Npc/Footprints/Humanoid", .pos= pos, .origin= sf::Vector2f{
            static_cast<float>(size.x / 2), static_cast<float>(size.y / 2)}, .defaultFrame= sf::IntRect{0, 0,
                                                                                                        static_cast<int>(size.x),
                                                                                                        static_cast<int>(size.y)}};
    FootprintGenerator footprintGenerator{
            spriteConfig,
             size.y * 3,
            {size.x / 3, size.y / 3},
            pos
    };
    setSurfaceEffectGenerator(std::make_unique<FootprintGenerator>(footprintGenerator));
}


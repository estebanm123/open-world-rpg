
#include "BeastInitializers.h"
#include "../../../../../Animation/RepeatingAnim.h"
#include "../../Collision Physics/BlockingPhysics.h"
#include "../NPC AI/Activities/RandomTravel.h"
#include "../NPC AI/Activities/Activity Managers/ActivityManager.h"
#include "../../Hitbox/ViewCone.h"
#include "../NPC AI/NpcAi.h"

const std::string NPC_FOLDER = "Npc/Shadow/";

constexpr int CAT_FRAME_WIDTH = 27;
constexpr int CAT_FRAME_HEIGHT = 50;
constexpr float CAT_HITBOX_WIDTH = 9;
constexpr float CAT_HITBOX_HEIGHT = 29;

std::unique_ptr<BaseActivity<Beast>> CatInitializer::generateActivities(BeastInitializer::Position pos) {
    auto testActivities = ActivityManager<Beast>::Activities{};
    auto randTravel = std::make_unique<RandomTravel<Beast>>(50.f, pos, 150.f);
    testActivities.push_front(std::move(randTravel));
    return std::make_unique<ActivityManager<Beast>>(std::move(testActivities));
}

CollidableEntity::Config CatInitializer::generateHitbox(BeastInitializer::Position pos) {

    auto secondaryHitboxes = MultiHitbox::Hitboxes {};
    secondaryHitboxes.push_back(std::make_unique<ViewCone>(pos, 100, CAT_HITBOX_WIDTH, 100));
    return CollidableEntity::Config {std::make_unique<SingleHitbox>(sf::FloatRect{pos.x, pos.y, CAT_HITBOX_WIDTH, CAT_HITBOX_HEIGHT}, 0, std::make_unique<BlockingPhysics>()),
                                     std::make_unique<MultiHitbox>(std::move(secondaryHitboxes))};

}

std::unique_ptr<SpriteReg>
CatInitializer::generateSprite(BeastInitializer::Position pos, std::unique_ptr<AnimationPlayer> animPlayer) {
    return std::make_unique<ShadowedSpriteReg>(ShadowedSpriteReg{
            NPC_FOLDER + "Cat",
            pos,
            {CAT_FRAME_WIDTH / 2.f, CAT_FRAME_HEIGHT / 2.f},
            std::move(animPlayer)});
}

std::unique_ptr<AnimationPlayer> CatInitializer::generateAnimPlayer(BeastInitializer::Position pos) {
    std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
    anims.insert({&MoveableActions::Idle, std::make_unique<RepeatingAnim>(
            Animation::Metadata{CAT_FRAME_WIDTH, CAT_FRAME_HEIGHT, 2, 4, 0, 250, {4}})});
    anims.insert({&MoveableActions::Move, std::make_unique<RepeatingAnim>(
            Animation::Metadata{CAT_FRAME_WIDTH, CAT_FRAME_HEIGHT, 0, 2, 0, 150, {2}, Animation::Priority::LOW, 0,
                                true})});
    return std::make_unique<AnimationPlayer>(std::move(anims));
}

constexpr int SNAKE_FRAME_WIDTH = 12;
constexpr int SNAKE_FRAME_HEIGHT = 34;
constexpr int SNAKE_HITBOX_WIDTH = 10;
constexpr int SNAKE_HITBOX_HEIGHT = 29;

std::unique_ptr<BaseActivity<Beast>> SnakeInitializer::generateActivities(BeastInitializer::Position pos) {
    auto testActivities = ActivityManager<Beast>::Activities{};
    auto randTravel = std::make_unique<RandomTravel<Beast>>(5.f, pos, 100.f);
    testActivities.push_front(std::move(randTravel));
    return std::make_unique<ActivityManager<Beast>>(std::move(testActivities));
}

CollidableEntity::Config SnakeInitializer::generateHitbox(BeastInitializer::Position pos) {
    return CollidableEntity::Config{ std::make_unique<SingleHitbox>(
            sf::FloatRect{pos.x, pos.y, SNAKE_HITBOX_WIDTH, SNAKE_HITBOX_HEIGHT}, 0,
            std::make_unique<BlockingPhysics>())};
}

std::unique_ptr<SpriteReg>
SnakeInitializer::generateSprite(BeastInitializer::Position pos, std::unique_ptr<AnimationPlayer> animPlayer) {
    return std::make_unique<SpriteReg>(
            SpriteReg::Config{NPC_FOLDER + "Snake", pos, {SNAKE_FRAME_WIDTH / 2.f, SNAKE_FRAME_HEIGHT / 2.f},
                              std::move(animPlayer)});
}

std::unique_ptr<AnimationPlayer> SnakeInitializer::generateAnimPlayer(BeastInitializer::Position pos) {
    std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
    anims.insert({&MoveableActions::Idle, std::make_unique<RepeatingAnim>(
            Animation::Metadata{SNAKE_FRAME_WIDTH, SNAKE_FRAME_HEIGHT, 2, 4, 0, 300, {4}, Animation::Priority::LOW,
                                30})});
    anims.insert({&MoveableActions::Move, std::make_unique<RepeatingAnim>(
            Animation::Metadata{SNAKE_FRAME_WIDTH, SNAKE_FRAME_HEIGHT, 0, 2, 0, 300, {2}, Animation::Priority::LOW, 30,
                                true})});
    return std::make_unique<AnimationPlayer>(std::move(anims));
}

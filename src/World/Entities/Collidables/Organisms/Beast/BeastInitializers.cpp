
#include "BeastInitializers.h"
#include "../../../../../Animation/RepeatingAnim.h"
#include "../../../Sprites/ShadowedSpriteReg.h"
#include "../../Collision Physics/BlockingPhysics.h"
#include "../../Hitbox/SingleHitbox.h"
#include "../NPC AI/Activities/Activities/RandomTravel.h"

const std::string NPC_FOLDER = "Npc/Shadow/";

constexpr int CAT_FRAME_WIDTH = 27;
constexpr int CAT_FRAME_HEIGHT = 50;
constexpr float CAT_HITBOX_WIDTH = 9;
constexpr float CAT_HITBOX_HEIGHT = 29;

std::unique_ptr<BaseActivity<Beast>> CatInitializer::generateActivities(BeastInitializer::Position pos) {
    auto testActivities = ActivityManager<Beast>::Activities{};
    auto randTravel = std::make_unique<RandomTravel<Beast>>(5.f, pos, 100.f);
    testActivities.push_front(std::move(randTravel));
    return std::make_unique<ActivityManager<Beast>>(std::move(testActivities));
}

std::unique_ptr<Hitbox> CatInitializer::generateHitbox(BeastInitializer::Position pos) {
    return std::make_unique<SingleHitbox>(
            sf::FloatRect{pos.x, pos.y, CAT_HITBOX_WIDTH, CAT_HITBOX_HEIGHT}, 0, std::make_unique<BlockingPhysics>());
}

ShadowedSpriteReg
CatInitializer::generateSprite(BeastInitializer::Position pos, std::unique_ptr<AnimationPlayer> animPlayer) {
    return ShadowedSpriteReg{
            NPC_FOLDER + "Cat",
            pos,
            {CAT_FRAME_WIDTH / 2.f, CAT_FRAME_HEIGHT / 2.f},
            std::move(animPlayer)};
}

std::unique_ptr<AnimationPlayer> CatInitializer::generateAnimPlayer(BeastInitializer::Position pos) {
    std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
    anims.insert({&MoveableActions::Idle, std::make_unique<RepeatingAnim>(
            Animation::Metadata{CAT_FRAME_WIDTH, CAT_FRAME_HEIGHT, 2, 4, 0, 200, {4}})});
    anims.insert({&MoveableActions::Move, std::make_unique<RepeatingAnim>(
            Animation::Metadata{CAT_FRAME_WIDTH, CAT_FRAME_HEIGHT, 0, 2, 0, 130, {2}, Animation::Priority::LOW, 0,
                                true})});
    return std::make_unique<AnimationPlayer>(std::move(anims));
}

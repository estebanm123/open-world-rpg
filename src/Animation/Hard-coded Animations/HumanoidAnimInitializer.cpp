

#include "HumanoidAnimInitializer.h"
#include "../../World/Entities/Collidables/MoveableEntity.h"
#include "../RepeatingAnim.h"
#include "../AnimationPlayer.h"
#include "../../World/Entities/Collidables/Organisms/Humanoid/Humanoid.h"
#include "../NonRepeatingAnim.h"
#include <unordered_map>

constexpr int BASE_FRAME_WIDTH = Humanoid::BASE_FRAME_WIDTH;
constexpr int BASE_FRAME_HEIGHT = Humanoid::BASE_FRAME_WIDTH;

constexpr int BODY_IDLE_DELAY = 200;
constexpr int BODY_MOVE_DELAY = 100;
constexpr int BODY_TOUCH_DELAY = 450;

constexpr int HEAD_BASIC_DELAY = 100;

std::unique_ptr<AnimationPlayer> HumanoidAnimInitializer::initializeEmptyBody() {
    std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
    anims.insert({&MoveableActions::Idle, std::make_unique<RepeatingAnim>(
            Animation::Metadata{BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, 6, 8, 0, BODY_IDLE_DELAY, {8}})});
    anims.insert({&MoveableActions::Move, std::make_unique<RepeatingAnim>(
            Animation::Metadata{BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, 0, 2, 0, BODY_MOVE_DELAY, {2, 5}})});
    anims.insert({&HumanoidActions::Touch, std::make_unique<NonRepeatingAnim>(
            Animation::Metadata{BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, 8, 12, 0, BODY_TOUCH_DELAY, {12}, Animation::Priority::HIGH})});
    return std::make_unique<AnimationPlayer>(std::move(anims));
}


std::unique_ptr<AnimationPlayer> HumanoidAnimInitializer::initializeEmptyHead() {
    std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
    anims.insert({&MoveableActions::Move, std::make_unique<RepeatingAnim>(
            Animation::Metadata{BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, 0, 4, 0, HEAD_BASIC_DELAY, {2,4}})});
    return std::make_unique<AnimationPlayer>(std::move(anims));
}


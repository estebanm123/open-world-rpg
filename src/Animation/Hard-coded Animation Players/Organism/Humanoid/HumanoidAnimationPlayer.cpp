

#include "HumanoidAnimationPlayer.h"

HumanoidAnimationPlayer::HumanoidAnimationPlayer(EntitySprite &sprite, std::shared_ptr<Animation> moveAnim,
                                                 std::shared_ptr<Animation> idleAnim,
                                                 std::shared_ptr<Animation> useAnim) : OrganismAnimationPlayer(sprite,
                                                                                                               std::move(
                                                                                                                       moveAnim),
                                                                                                               std::move(
                                                                                                                       idleAnim)),
                                                                                       useAnim(std::move(useAnim)) {}

void HumanoidAnimationPlayer::playUseAnim() {
    playAnim(useAnim);
}
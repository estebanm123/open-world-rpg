

#include "OrganismAnimationPlayer.h"

OrganismAnimationPlayer::OrganismAnimationPlayer(EntitySprite &sprite, std::shared_ptr<Animation> moveAnim,
                                                 std::shared_ptr<Animation> idleAnim) : MoveableAnimationPlayer(sprite,
                                                                                                                std::move(
                                                                                                                        moveAnim),
                                                                                                                std::move(
                                                                                                                        idleAnim)) {}
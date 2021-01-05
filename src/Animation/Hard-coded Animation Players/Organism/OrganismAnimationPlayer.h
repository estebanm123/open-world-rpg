#pragma once

#include "../MoveableAnimationPlayer.h"

class OrganismAnimationPlayer : public MoveableAnimationPlayer {

public:
    OrganismAnimationPlayer(EntitySprite *sprite, std::shared_ptr<Animation> moveAnim,
                            std::shared_ptr<Animation> idleAnim);
};





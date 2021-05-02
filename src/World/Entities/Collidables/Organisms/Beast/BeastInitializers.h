#pragma once


#include "BeastInitializer.h"

struct CatInitializer : public BeastInitializer {

protected:
    std::unique_ptr<BaseActivity<Beast>> generateActivities(Position pos) override;

    std::unique_ptr<Hitbox> generateHitbox(Position pos) override;

    SpriteReg generateSprite(Position pos, std::unique_ptr<AnimationPlayer> animPlayer) override;

    std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) override;
};





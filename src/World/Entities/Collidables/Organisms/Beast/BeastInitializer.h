#pragma once


#include "Beast.h"
#include "../../../../../Util/Initializer/ArgDependentInitializer.h"
#include "../NPC AI/Activities/BaseActivity.h"
#include "../../../../../Animation/AnimationPlayer.h"

// Note: Don't abstract a generic initializer for humanoids - it's gonna depend on a lot more
//      factors eg. faction, env, settlement
struct BeastInitializer : public ArgDependentInitializer<Beast, sf::Vector2f> {
    typedef sf::Vector2f Position;

    std::unique_ptr<Beast> initialize(Position pos) override;

protected:
    virtual std::unique_ptr<BaseActivity<Beast>> generateActivities(Position pos) = 0;

    virtual std::unique_ptr<SingleHitbox> generateHitbox(Position pos) = 0;

    virtual std::unique_ptr<SpriteReg> generateSprite(Position pos, std::unique_ptr<AnimationPlayer> animPlayer) = 0;

    virtual std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) = 0;
};




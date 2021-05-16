#pragma once


#include "BeastInitializer.h"

struct CatInitializer : public BeastInitializer {

protected:
    std::unique_ptr<BaseActivity<Beast>> generateActivities(Position pos) override;

    CollidableEntity::Config generateHitbox(Position pos) override;

    std::unique_ptr<SpriteReg> generateSprite(Position pos, std::unique_ptr<AnimationPlayer> animPlayer) override;

    std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) override;

    float getSpeed() override;
};

struct SnakeInitializer : public BeastInitializer {
protected:
    std::unique_ptr<BaseActivity<Beast>> generateActivities(Position pos) override;

    float getSpeed() override;

    CollidableEntity::Config generateHitbox(Position pos) override;

    std::unique_ptr<SpriteReg> generateSprite(Position pos, std::unique_ptr<AnimationPlayer> animPlayer) override;

    std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) override;
};

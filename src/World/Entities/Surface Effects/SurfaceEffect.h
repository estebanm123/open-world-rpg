#pragma once

#include "../Entity.h"
#include "../Sprites/SpriteReg.h"

class SurfaceEffect : public Entity {
public:
    // For animated SurfaceEffects
    SurfaceEffect(SpriteReg::Config config);

    SurfaceEffect(SpriteReg::CopyableConfig config);

    void update(float dt) override;

    bool isFinished();

    void accept(EntityVisitor *visitor) override;

protected:
    EntitySprite &getSprite() override;

private:
    SpriteReg sprite;
    bool hasDefaultAnim;
    // todo: ttl/ mark for fade
};

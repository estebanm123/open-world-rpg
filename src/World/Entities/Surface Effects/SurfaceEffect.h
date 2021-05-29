#pragma once

#include "../Entity.h"
#include "../Sprites/SpriteReg.h"

class SurfaceEffect : public Entity {
public:
    SurfaceEffect(SpriteReg::CopyableConfig config);

    void update(float dt) override;

    void accept(EntityVisitor *visitor) override;

protected:
    EntitySprite &getSprite() override;

private:
    SpriteReg sprite;
    // todo: ttl/ mark for fade
};

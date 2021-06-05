#pragma once

#include <memory>
#include "../../World Generation/Environments/Env.h"

class SurfaceEffect;

class MoveableEntity;

class SurfaceEffectGenerator {
public:
    virtual std::unique_ptr<SurfaceEffect> generateSurfaceEffect(MoveableEntity *moveable, int *env) = 0;
};

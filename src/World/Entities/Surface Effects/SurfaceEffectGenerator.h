#pragma once

#include <memory>

class SurfaceEffect;

class MoveableEntity;

class SurfaceEffectGenerator {
public:
    virtual std::unique_ptr<SurfaceEffect> generateSurfaceEffect(MoveableEntity * moveable) = 0;
};

#pragma once

#include "Random.h"

struct GlobalRand {
    inline static Random<> rand;

    static void initGlobalRand(int seed);

    static float getRandAngle();
};
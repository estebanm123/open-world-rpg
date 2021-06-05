

#include "GlobalRand.h"

void GlobalRand::initGlobalRand(int seed) {
    GlobalRand::rand = Random{seed};
}

float GlobalRand::getRandAngle() {
    return rand.getFloatInRange(0, 360);
}

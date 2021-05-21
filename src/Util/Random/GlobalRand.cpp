

#include "GlobalRand.h"

void GlobalRand::initGlobalRand(int seed) {
    GlobalRand::rand = Random{seed};
}

#include "NeighboredEnv.h"



bool NeighboredEnv::isPriorityEnv() const {
    return isPriority;
}

void NeighboredEnv::togglePriority() {
    isPriority = !isPriority;
}




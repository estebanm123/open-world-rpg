#include "NeighboredEnv.h"

#include "../CompleteEnv.h"

bool NeighboredEnv::isPriorityEnv() const { return isPriority; }

void NeighboredEnv::togglePriority() { isPriority = !isPriority; }

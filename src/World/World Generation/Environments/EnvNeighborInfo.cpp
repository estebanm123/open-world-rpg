

#include "EnvNeighborInfo.h"

EnvNeighborInfo::EnvNeighborInfo(Env::EnvId neighbor, int numSplits, int numCorners)
	: neighbor(neighbor),
	  numCorners(numCorners),
	  numSplits(numSplits) {}

#pragma once

#include "Env.h"

struct EnvNeighborInfo {
	EnvNeighborInfo(Env::EnvId neighbor, int numSplits, int numCorners);

	Env::EnvId neighbor;
	int numSplits;
	int numCorners;
};

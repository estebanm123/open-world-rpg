#pragma once

#include "../../../../../Util/Initializer/PositionBasedInitializerPool.h"
#include "Beast.h"

struct DirtBeastFactory : PositionBasedInitializerPool<Beast> {
	DirtBeastFactory();
};

struct SandBeastFactory : PositionBasedInitializerPool<Beast> {
	SandBeastFactory();
};

struct WaterBeastFactory : PositionBasedInitializerPool<Beast> {
	WaterBeastFactory();
};

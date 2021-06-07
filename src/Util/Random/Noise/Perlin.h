#pragma once

#include "../../MathExtra.h"

class Perlin {
public:
	static float generateNoise(int seed, float x, float y);

	// todo: create option to store seed as state
private:
	static const int PrimeX = 501125321;
	static const int PrimeY = 1136930381;
};
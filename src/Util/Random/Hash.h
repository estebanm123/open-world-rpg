
#pragma once

#include <stdexcept>

const inline int RAND_MIXER_1 = 0x45d91995;
const inline int RAND_MIXER_2 = 0x27d4eb2d;
// const inline int RAND_MIXER_2 = 24;

// May not yield results as random-looking as mixCoordsHeavy at the cost of performance.
template <typename T, typename X = T>
inline int mixCoords(T a, T b, int seed = RAND_MIXER_1) {
	auto inta = static_cast<int>(a);  // we don't care about the decimal; integer precision will be handled later
	auto intb = static_cast<int>(b);

	int hash = seed ^ inta ^ intb;
	hash *= RAND_MIXER_2;
	hash ^= hash >> 15;
	return hash;
}

// Todo: benchmark
template <typename T>
inline int mixCoordsHeavy(T a, T b, int seed = RAND_MIXER_1) {
	auto inta = static_cast<int>(a);  // we don't care about the decimal; integer precision will be handled later
	auto intb = static_cast<int>(b);

	int h = seed + inta * 374761393 + intb * 668265263;
	h = (h ^ (h >> 13)) * 1274126177;
	return h ^ (h >> 16);
}

template <typename T, typename X = T>
inline int hash2ValuesModSize(T a, T b, X size, int seed = RAND_MIXER_1) {
	if (size == 0) throw std::runtime_error("Trying to hash w/ size 0!");
	// todo: add assertion to confirm types and sizes (size != 0)]
	int hash = mixCoords(a, b, seed);
	return abs(hash % size);
}

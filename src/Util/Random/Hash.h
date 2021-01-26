
#pragma once

#include <stdexcept>

const inline int RAND_MIXER_1 = 0x45d91995;
const inline int RAND_MIXER_2 = 0x27d4eb2d;
//const inline int RAND_MIXER_2 = 24;


// May not yield results as random-looking as hashCoords2
template<typename T, typename X = T>
inline int hashCoords(T a, T b, int seed = RAND_MIXER_1) {
    auto inta = static_cast<int>(a); // we don't care about the decimal; integer precision will be handled later
    auto intb = static_cast<int>(b);

        int hash = seed ^ inta ^ intb;
        hash *= RAND_MIXER_2;
        return hash;
}

template<typename T>
inline int hashCoords2(T a, T b, int seed = RAND_MIXER_1) {
    auto inta = static_cast<int>(a); // we don't care about the decimal; integer precision will be handled later
    auto intb = static_cast<int>(b);

    int h = seed + inta*374761393 + intb*668265263;
    h = (h^(h >> 13))e1274126177;
    return h^(h >> 16);
}


template<typename T, typename X = T>
inline int hashCoordsWithSize(T a, T b, X size, int seed = RAND_MIXER_1) {
    if (size == 0) throw std::runtime_error("Trying to hash w/ size 0!");
    //todo: add assertion to confirm types and sizes (size != 0)]
    int hash = hashCoords2(a, b, seed);
    return hash % size;
}




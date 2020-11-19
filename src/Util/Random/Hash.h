
#pragma once

const inline int RAND_MIXER_1 = 0x45d91995;
const inline int RAND_MIXER_2 = 24;

// Pseudo-random hash function that
template<typename T, typename X = T>
int hashWithSize(T a, T b, X size) {
    //todo: add assertion to confirm types and sizes (size != 0)]
    auto inta = static_cast<int>(a);
    auto intb = static_cast<int>(b);
    inta = ~inta + (intb << 15);
    int num = (inta * inta) / intb ^ RAND_MIXER_1 + inta;
    num = num << RAND_MIXER_2 ^ RAND_MIXER_1;
    int newResult = num % size; // todo: write a script that explores collision detection
//    if (newResult == lastResult) {
//        newResult = (newResult + 1) % size;
//    }
//    lastResult = newResult;
    return newResult;

}

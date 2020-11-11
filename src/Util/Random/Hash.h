
#pragma once

const inline int RAND_MIXER_1 = 0x45d91995;
const inline int RAND_MIXER_2 = 24;

template<typename T, typename X = T>
int hashWithSize(T a, T b, X size) {

    //todo: add assertion to confirm types and sizes (size != 0)]
    int inta = static_cast<int>(a);
    int intb = static_cast<int>(b);
    inta = ~inta + (intb << 15);
    int num1 = (inta * inta) / intb ^ RAND_MIXER_1 + inta;
    num1 = num1 << RAND_MIXER_2 ^ RAND_MIXER_1;
    return num1 % size; // todo: write a script that explores collision detection
}


#pragma once

template<typename T, typename X = T>
int hashWithSize(T a, T b, X size) {
    return static_cast<int>(a * b % 7 % size); // todo: write a script that explores collision detection
}


#pragma once


#include "StatTypes.h"

class Stat {
public:
    struct Level {
        Level() = default;
        explicit Level(float defaultValue);
        // Format example: 20% - percentChange = .2
        void change(float percentChange);

        float getValue();

    private:
//        const float minValue = 0;
//        const float maxValue = 100;

        float value = 0;

    };

    Stat(const Level &level);

    float value();

    void update(float dt);
//      todo: update + change

private:
    Level level;

};





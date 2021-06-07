

#include "Stat.h"

Stat::Level::Level(float value) : value(value) {}

void Stat::Level::change(float percentChange) {
	value += percentChange * value;
	//    if (value > maxValue) {
	//        value = maxValue;
	//    } else if (value < minValue) {
	//        value = minValue;
	//    }
}

float Stat::Level::getValue() { return value; }

Stat::Stat(const Stat::Level &level) : level(level) {}

float Stat::value() { return level.getValue(); }

void Stat::update(float dt) {}

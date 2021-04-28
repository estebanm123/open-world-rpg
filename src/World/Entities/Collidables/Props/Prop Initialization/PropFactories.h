#pragma once


#include "PropFactory.h"

struct SandPropFactory : public PropFactory {
    SandPropFactory();
};

struct DirtPropFactory : public PropFactory {
    DirtPropFactory();
};

struct WaterPropFactory : public PropFactory {
    WaterPropFactory();
};

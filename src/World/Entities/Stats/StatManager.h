#pragma once


#include <unordered_map>
#include <memory>
#include <utility>
#include "StatTypes.h"
#include "Stat.h"


class StatManager {
public:
    explicit StatManager(std::unordered_map<StatType *, std::unique_ptr<Stat>> stats);

    void update(float dt);

    float getValue(StatType * statType);
private:
    std::unordered_map<StatType *, std::unique_ptr<Stat>> stats;
};



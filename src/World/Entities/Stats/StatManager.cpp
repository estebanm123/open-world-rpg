

#include "StatManager.h"

StatManager::StatManager(std::unordered_map<StatType *, std::unique_ptr<Stat>> stats) : stats(std::move(stats)) {}

void StatManager::update(float dt) {
    for (auto const&[key, stat] : stats) {
        stat->update(dt);
    }
}

float StatManager::getValue(StatType *statType) {
    return stats.at(statType)->value();
}

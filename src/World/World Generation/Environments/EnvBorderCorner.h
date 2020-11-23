#pragma once
#include "EnvBorderData.h"

struct EnvBorderCorner : public EnvBorderData {
    EnvBorderCorner(const Env & primary, const Env & secondary, int rotationAngle = 0);
    std::unordered_set<NeighboredEnv> getCompatibleNeighbors(const sf::Vector2i & direction) const override;
    bool operator==(const NeighboredEnv &other) const override;
    int rotationAngle
};





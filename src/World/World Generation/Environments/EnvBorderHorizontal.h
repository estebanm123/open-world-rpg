#pragma once
#include "EnvBorderData.h"

class EnvBorderHorizontal : public EnvBorderData {
public:
    bool operator==(const NeighboredEnv & other) const override;
    std::unordered_set<NeighboredEnv> getCompatibleNeighbors(const sf::Vector2i & direction) const;
};


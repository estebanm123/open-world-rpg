#pragma once
#include "CompleteEnv.h"

class Env : public CompleteEnv {
public:
    std::shared_ptr<TileContainer> selectTileContainer(const sf::Vector2f & coords) const override;
    std::unordered_set<NeighboredEnv> getCompatibleNeighbors(const sf::Vector2i &direction) const override;
    bool operator==(const NeighboredEnv & other) const override;
};
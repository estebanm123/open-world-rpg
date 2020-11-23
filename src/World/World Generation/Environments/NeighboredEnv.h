#pragma once

#include <unordered_set>
#include <SFML/System.hpp>
#include "../../../Util/NonMoveable.h"

class NeighboredEnv {
public:
    virtual std::unordered_set<NeighboredEnv> getCompatibleNeighbors(const sf::Vector2i & direction) const = 0;
    virtual bool operator==(const NeighboredEnv & other) const= 0;
};





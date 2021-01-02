#pragma once

#include "EnvBorderData.h"

struct EnvBorderHorizontal : public EnvBorderData {
    EnvBorderHorizontal(const std::shared_ptr<EnvWrapper> &primary, const std::shared_ptr<EnvWrapper> &secondary);

    bool handleEquality(const std::shared_ptr<NeighboredEnv> &other) override;

    NeighboredEnv::Neighbors getCompatibleNeighbors(const sf::Vector2i &direction) const override;

    std::string toString() const override;
};


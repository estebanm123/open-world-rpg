#pragma once

#include "CompleteEnv.h"

class EnvBorder : public CompleteEnv {
public:
    std::shared_ptr<TileContainer> selectTileContainer(const sf::Vector2f & coords) const override;
};





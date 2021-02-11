#pragma once

#include "CompleteEnv.h"

class EnvBorder : public CompleteEnv {
public:
    std::unique_ptr<Prop> generateProp(const sf::Vector2f &propCoords, bool isDecor) const override;

};





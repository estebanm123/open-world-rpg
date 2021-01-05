#pragma once

#include "CompleteEnv.h"

class EnvBorder : public CompleteEnv {
public:
    bool isBorder() const override;

    bool operator==(const CompleteEnv& other) const override;

    std::unique_ptr<InteractiveProp> generateInteractiveProp(const sf::Vector2f& propCoords) const override;

    std::unique_ptr<DecorProp> generateDecorProp(const sf::Vector2f& propCoords) const override;
};





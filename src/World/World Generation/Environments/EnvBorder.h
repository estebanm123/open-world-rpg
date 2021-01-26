#pragma once

#include "CompleteEnv.h"

class EnvBorder : public CompleteEnv {
public:
    bool isBorder() const override;

    bool operator==(const CompleteEnv& other) const override;

    std::unique_ptr<Prop> generateProp(const sf::Vector2f& propCoords) const override;

};





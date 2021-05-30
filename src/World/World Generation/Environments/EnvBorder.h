#pragma once

#include "CompleteEnv.h"

class EnvBorder : public CompleteEnv {
public:
    std::unique_ptr<Prop> generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const override;

    std::unique_ptr<Beast> generateBeast(const sf::Vector2f &beastCoords) const override;

    const std::vector<std::unique_ptr<SurfaceEffectGenerator>> * getSurfaceEffectGenerators() const override;

    int *getId() const override;
};

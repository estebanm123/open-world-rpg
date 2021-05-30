#pragma once

#include <string>
#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "../../../Util/Random/Hash.h"

class Beast;

class Prop;

class SurfaceEffectGenerator;

class CompleteEnv {
public:
    virtual ~CompleteEnv() = default;

    virtual int * getId() const = 0;

    virtual std::unique_ptr<Prop> generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const = 0;

    virtual std::unique_ptr<Beast> generateBeast(const sf::Vector2f & beastCoords) const = 0;

    virtual const std::vector<std::unique_ptr<SurfaceEffectGenerator>> * getSurfaceEffectGenerators() const = 0;

};







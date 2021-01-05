#pragma once

#include <string>
#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "../../../Util/Random/Hash.h"

class InteractiveProp;
class DecorProp;

class CompleteEnv {
public:
    virtual ~CompleteEnv() = default;

    virtual bool isBorder() const = 0;

    virtual bool operator==(const CompleteEnv& other) const = 0;

    virtual std::unique_ptr<InteractiveProp> generateInteractiveProp(const sf::Vector2f& propCoords) const = 0;

    virtual std::unique_ptr<DecorProp> generateDecorProp(const sf::Vector2f& propCoords) const = 0;
protected:

};







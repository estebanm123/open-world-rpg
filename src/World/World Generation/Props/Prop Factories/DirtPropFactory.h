#pragma once

#include "PropFactory.h"

class DirtPropFactory : public PropFactory {
public:
    std::unique_ptr<InteractiveProp> generateInteractiveProp(int hashVal, const sf::Vector2f &propCoords) override;

    std::unique_ptr<DecorProp> generateDecorProp(int hashVal, const sf::Vector2f &propCoords) override;

private:
    static constexpr auto ROCK_MIN = HASH_LIM * .94;
};



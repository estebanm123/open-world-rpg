#pragma once

#include "PropFactory.h"

class DirtPropFactory : public PropFactory {
public:
    std::unique_ptr<Prop> generateProp(int hashVal, const sf::Vector2f &propCoords) override;

private:
    static constexpr auto ROCK_MIN = HASH_LIM * .98;
    static constexpr auto BUSH_MIN = HASH_LIM * .92;
};



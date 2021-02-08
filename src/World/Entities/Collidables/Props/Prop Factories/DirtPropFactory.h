#pragma once

#include "PropFactory.h"

class DirtPropFactory : public PropFactory {
public:
    std::unique_ptr<Prop> generateMainProp(int hashVal, const sf::Vector2f &propCoords) override;

    std::unique_ptr<Prop> generateDecorProp(int hashVal, const sf::Vector2f &propCoords) override;
private:
    // GENERATION THRESHOLDS - lower value = higher chance
    //Main
    static constexpr auto ROCK_MIN = HASH_LIM * .98;
    static constexpr auto BUSH_MIN = HASH_LIM * .93;
    //Decor
    static constexpr auto GRASS_COVER_MIN = HASH_LIM * .3;
};



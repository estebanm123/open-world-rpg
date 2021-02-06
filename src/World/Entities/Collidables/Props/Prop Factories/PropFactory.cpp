
#include "PropFactory.h"
#include "../Prop.h"
#include "../../../../../Util/Random/Hash.h"
#include "../../Collision Physics/BlockingPhysics.h"

constexpr auto SIZE_FLEX = 5; // temp

const std::array<sf::IntRect, 4> ROCK_SPRITESHEETS{{
                                                           {0, 0, 29, 28},
                                                           {29, 0, 52, 52},
                                                           {81, 0, 25, 29},
                                                           {106, 0, 29, 29}
                                                   }};


std::unique_ptr<Prop> PropFactory::generateRock(int hashVal, const sf::Vector2f &pos) {
    int selectedIndex = getPropIndex(hashVal, ROCK_SPRITESHEETS.size());
    const auto & spriteSheetCoords = ROCK_SPRITESHEETS[selectedIndex];
    const sf::Vector2f size = {static_cast<float>(spriteSheetCoords.width - SIZE_FLEX),
                               static_cast<float>(spriteSheetCoords.height - SIZE_FLEX)};
    return std::make_unique<Prop>("Foliage/Rocks", size, spriteSheetCoords,
                                  Prop::PropOptions{pos, std::make_unique<BlockingPhysics>()});
}

const std::array<sf::IntRect, 1> BUSH_SPRITESHEETS {{
                                                           {0, 0, 36, 32}
                                                   }};


std::unique_ptr<Prop> PropFactory::generateBush(int hashVal, const sf::Vector2f &pos) {
    int selectedIndex = getPropIndex(hashVal, BUSH_SPRITESHEETS.size());
    const auto & spriteSheetCoords = BUSH_SPRITESHEETS[selectedIndex];
    const sf::Vector2f size = {static_cast<float>(spriteSheetCoords.width - SIZE_FLEX),
                               static_cast<float>(spriteSheetCoords.height - SIZE_FLEX)};
    return std::make_unique<Prop>("Foliage/ForestFoliage", size, spriteSheetCoords,
                                  Prop::PropOptions{pos, std::make_unique<BlockingPhysics>()});
}

std::unique_ptr<Prop> PropFactory::generateProp(const sf::Vector2f &propCoords) {
    return generateProp(hash2ValuesModSize(propCoords.x, propCoords.y, HASH_LIM), propCoords);
}

int PropFactory::normalizeHashValue(int hashVal, int minimum) {
    auto relativeUpperBound = static_cast<float>(HASH_LIM - minimum);
    auto relativeHashVal = static_cast<float>(hashVal - minimum);
    float proportionOfRelativeZone = relativeHashVal / relativeUpperBound;
    return static_cast<int>(proportionOfRelativeZone * HASH_LIM); // reset as proportion to HASH_LIM
}

int PropFactory::getPropIndex(int hashVal, int numProps) {
    return hashVal % numProps;
}



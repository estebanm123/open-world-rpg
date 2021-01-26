
#include "PropFactory.h"
#include "../Prop.h"
#include "../../../../../Util/Random/Hash.h"
#include "../../Collision Physics/BlockingPhysics.h"

std::unique_ptr<Prop> PropFactory::generateRocks(int hashVal, const sf::Vector2f &propCoords) {
    int selectedIndex = getPropIndex(hashVal, 4);
    switch (selectedIndex) {
        case 0:
            return generateRock(propCoords, {0, 0, 29, 28});
        case 1:
            return generateRock(propCoords, {29, 0, 52, 52});
        case 2:
            return generateRock(propCoords, {81, 0, 25, 29});
        default:
            return generateRock(propCoords, {106, 0, 29, 29});
    }
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

std::unique_ptr<Prop> PropFactory::generateRock(const sf::Vector2f &pos, const sf::IntRect &spriteSheetCoords) {
    const sf::Vector2f size = {static_cast<float>(spriteSheetCoords.width),
                               static_cast<float>(spriteSheetCoords.height)};
    return std::make_unique<Prop>("Foliage/Rocks", pos, size, std::make_unique<BlockingPhysics>(),
                                             std::make_unique<AnimationPlayer>(), spriteSheetCoords);
}

std::unique_ptr<Prop> PropFactory::generateProp(const sf::Vector2f &propCoords) {
    return generateProp(hashCoordsWithSize(propCoords.x, propCoords.y, HASH_LIM), propCoords);
}


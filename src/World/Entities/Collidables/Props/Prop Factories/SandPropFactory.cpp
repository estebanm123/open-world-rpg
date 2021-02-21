

#include "SandPropFactory.h"
#include "../Prop.h"


std::unique_ptr<Prop> SandPropFactory::generateMainProp(int hashVal, const sf::Vector2f &propCoords) {
    if (hashVal > ROCK_MIN) {
        return generateRock(normalizeHashValue(hashVal, ROCK_MIN), propCoords);
    }
    if (hashVal > CACTUS_MIN) {
        return generateCactus(normalizeHashValue(hashVal, CACTUS_MIN), propCoords);
    }
    return nullptr;
}

std::unique_ptr<Prop> SandPropFactory::generateDecorProp(int hashVal, const sf::Vector2f &propCoords) {
    return nullptr;
}


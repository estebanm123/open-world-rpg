#include "DirtPropFactory.h"
#include "../Prop.h"


std::unique_ptr<Prop> DirtPropFactory::generateMainProp(int hashVal, const sf::Vector2f &propCoords) {
    if (hashVal > ROCK_MIN) {
        return generateRock(normalizeHashValue(hashVal, ROCK_MIN), propCoords);
    }
    if (hashVal > BUSH_MIN) {
        return generateBush(normalizeHashValue(hashVal, BUSH_MIN), propCoords);
    }
    return nullptr;
}

std::unique_ptr<Prop> DirtPropFactory::generateDecorProp(int hashVal, const sf::Vector2f &propCoords) {
    if (hashVal > GRASS_COVER_MIN) {
        return generateGrassCover(normalizeHashValue(hashVal, GRASS_COVER_MIN), propCoords);
    }
    return std::unique_ptr<Prop>();
}


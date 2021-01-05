#include "DirtPropFactory.h"
#include "../Prop.h"


std::unique_ptr<Prop>DirtPropFactory::generateInteractiveProp(int hashVal, const sf::Vector2f &propCoords) {
    if (hashVal > ROCK_MIN) {
        generateRocks(normalizeHashValue(hashVal, ROCK_MIN), propCoords);
    }
}

std::unique_ptr<DecorProp> DirtPropFactory::generateDecorProp(int hashVal, const sf::Vector2f &propCoords) {
    return nullptr;
}

#include "DirtPropFactory.h"
#include "../Prop.h"


std::unique_ptr<Prop> DirtPropFactory::generateProp(int hashVal, const sf::Vector2f &propCoords) {
    if (hashVal > ROCK_MIN) {
        return generateRock(normalizeHashValue(hashVal, ROCK_MIN), propCoords);
    }
    if (hashVal > BUSH_MIN) {
        return generateBush(normalizeHashValue(hashVal, BUSH_MIN), propCoords);
    }
}


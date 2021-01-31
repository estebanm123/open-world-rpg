#include "DirtPropFactory.h"
#include "../Prop.h"


std::unique_ptr<Prop> DirtPropFactory::generateProp(int hashVal, const sf::Vector2f &propCoords) {
    if (abs(hashVal) > ROCK_MIN) {
        return generateRocks(normalizeHashValue(hashVal, ROCK_MIN), propCoords);
    }
}


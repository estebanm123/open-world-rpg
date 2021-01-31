

#include <iostream>
#include "EnvSelector.h"
#include "EnvTypes.h"
#include "../../../Util/Random/Noise/Perlin.h"

const std::shared_ptr<Env> &EnvSelector::getEnvironment(sf::Vector2f coords) {
    // todo: feed seed from state
    auto noise = Perlin::generateNoise(1233, coords.x / 2000, coords.y / 2000);
    //   std::cout << noise << std::endl;

    if (noise > 0.2) {
        return EnvTypes::Water;
    } else {
        return EnvTypes::Dirt;
    }
}
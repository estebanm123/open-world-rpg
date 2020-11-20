

#include <iostream>
#include "EnvGenerator.h"
#include "EnvTypes.h"
#include "../../../Util/Random/Noise/Perlin.h"

const Env & EnvGenerator::getEnvironment(sf::Vector2f coords) {
    // TODO: hook up perlin noise
    // todo: feed seed from state
    auto noise = Perlin::generateNoise(1233, coords.x / 1000, coords.y / 1000);

 //   std::cout << noise << std::endl;

    if (noise > 0.2) {
        return EnvTypes::Water;
    } else {
        return EnvTypes::Dirt;
    }
}
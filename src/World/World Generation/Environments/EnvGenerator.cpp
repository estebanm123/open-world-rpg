

#include <iostream>
#include "EnvGenerator.h"
#include "EnvTypes.h"
#include "../../../Util/Random/Noise/Perlin.h"

int max = INT_MIN;
int min = INT_MIN;
const Env & EnvGenerator::getEnvironment(sf::Vector2f coords) {
    // TODO: hook up perlin noise
    // todo: feed seed from state
    auto noise = Perlin::generateNoise(1233, coords.x / 48, coords.y / 48);
    std::cout << noise << std::endl;
    return EnvTypes::Dirt;
}
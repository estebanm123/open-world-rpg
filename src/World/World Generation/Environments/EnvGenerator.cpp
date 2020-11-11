

#include "EnvGenerator.h"
#include "EnvTypes.h"


const Env & EnvGenerator::getEnvironment(sf::Vector2f coords) {
    // TODO: hook up perlin noise
    return EnvTypes::Dirt;
}
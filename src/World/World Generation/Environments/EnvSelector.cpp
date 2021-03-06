

#include "EnvSelector.h"

#include <iostream>

#include "../../../Util/Random/Noise/Perlin.h"
#include "EnvTypes.h"

const Env* EnvSelector::getEnvironment(sf::Vector2f coords) {
	// todo: feed seed from state
	auto noise = Perlin::generateNoise(1233, coords.x / 2000, coords.y / 2000);
	//   std::cout << noise << std::endl;

	if (noise > 0.2) {
		return EnvManager::getEnv(EnvTypes::WATER);
	} else if (noise > -0.4) {
		return EnvManager::getEnv(EnvTypes::DIRT);
	} else {
		return EnvManager::getEnv(EnvTypes::SAND);
	}
}
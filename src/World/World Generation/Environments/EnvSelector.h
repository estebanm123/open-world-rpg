#pragma once

#include <SFML/Audio.hpp>
#include <memory>

class Env;

struct EnvSelector {
	static const Env* getEnvironment(sf::Vector2f coords);
};

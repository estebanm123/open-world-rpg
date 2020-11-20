#pragma once

#include <memory>
#include <SFML/Audio.hpp>

class Env;

struct EnvSelector {
    static const Env & getEnvironment(sf::Vector2f coords);
};





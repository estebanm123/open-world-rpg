#pragma once

#include <memory>
#include <SFML/Audio.hpp>

class Env;

struct EnvGenerator {
    static const Env & getEnvironment(sf::Vector2f coords);
};





#pragma once

#include <memory>
#include <SFML/Audio.hpp>

class Env;

struct EnvSelector {
    static const std::shared_ptr<Env>& getEnvironment(sf::Vector2f coords);
};





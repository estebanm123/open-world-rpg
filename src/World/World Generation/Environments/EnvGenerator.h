#pragma once

#include <memory>
#include "Env.h"

struct EnvGenerator {
    static std::shared_ptr<Env> getEnvironment(sf::Vector2f coords);
};





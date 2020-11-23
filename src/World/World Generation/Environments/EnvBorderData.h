#pragma once
#include "NeighboredEnv.h"
#include <SFML/System.hpp>
#include <memory>

class Env;

struct EnvBorderData : public NeighboredEnv {
    EnvBorderData(std::shared_ptr<Env> primary, std::shared_ptr<Env> secondary);
    const std::shared_ptr<Env> primaryEnv;
    const std::shared_ptr<Env> secondaryEnv;
protected:
    // maybe abstract some virtual helpers
};





#pragma once

#include "CompleteEnv.h"
#include "Env.h"

class EnvRegularProxy : public CompleteEnv {
public:
    EnvRegularProxy(const Env * env);

    std::unique_ptr<Prop> generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const override;
private:
    const Env * env;
};





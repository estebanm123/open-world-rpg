#pragma once

#include "CompleteEnv.h"
#include "Env.h"

// Allows clients to 'own' an Env, especially useful for
// making CompleteEnv polymorphic (with subclasses like EnvBorder
// that can't be global like Env)
class EnvProxy : public CompleteEnv {
public:
    EnvProxy(const Env * env);

    std::unique_ptr<Prop> generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const override;
private:
    const Env * env;
};





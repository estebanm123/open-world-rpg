#pragma once

#include "CompleteEnv.h"
#include "Env.h"

// Allows clients to 'own' an Env, especially useful for
// making CompleteEnv polymorphic (with subclasses like EnvBorder
// that can't be global like Env)
class EnvProxy : public CompleteEnv {
public:
	EnvProxy(const Env *env);

	std::unique_ptr<Prop> generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const override;

	int *getId() const override;

	std::unique_ptr<Beast> generateBeast(const sf::Vector2f &propCoords) const override;

	const std::vector<std::unique_ptr<SurfaceEffectGenerator>> *getSurfaceEffectGenerators() const override;

private:
	const Env *env;
};

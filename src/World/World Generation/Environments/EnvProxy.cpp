

#include "EnvProxy.h"

#include "../../Entities/Collidables/Organisms/NPC AI/NpcAi.h"
#include "../../Entities/Collidables/Props/Prop.h"

EnvProxy::EnvProxy(const Env *env) : env(env) {}

std::unique_ptr<Prop> EnvProxy::generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const {
	return env->generateEnvironmentalProp(propCoords, isDecor);
}

std::unique_ptr<Beast> EnvProxy::generateBeast(const sf::Vector2f &propCoords) const {
	return env->generateBeast(propCoords);
}

const std::vector<std::unique_ptr<SurfaceEffectGenerator>> *EnvProxy::getSurfaceEffectGenerators() const {
	return env->getSurfaceEffectGenerators();
}

int *EnvProxy::getId() const { return env->getId(); }

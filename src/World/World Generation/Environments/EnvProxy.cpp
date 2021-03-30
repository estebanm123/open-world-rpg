

#include "../../Entities/Collidables/Props/Prop.h"
#include "EnvProxy.h"

EnvProxy::EnvProxy(const Env *env) : env(env) {

}

std::unique_ptr<Prop> EnvProxy::generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const {
    return env->generateEnvironmentalProp(propCoords, isDecor);
}

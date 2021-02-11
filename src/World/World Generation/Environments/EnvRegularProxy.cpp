

#include "../../Entities/Collidables/Props/Prop.h"
#include "EnvRegularProxy.h"

EnvRegularProxy::EnvRegularProxy(const Env *env) : env(env) {

}

std::unique_ptr<Prop> EnvRegularProxy::generateProp(const sf::Vector2f &propCoords, bool isDecor) const {
    return env->generateProp(propCoords, isDecor);
}

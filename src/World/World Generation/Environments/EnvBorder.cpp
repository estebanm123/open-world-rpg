

#include "EnvBorder.h"

#include "../../Entities/Collidables/Props/Prop.h"

bool EnvBorder::isBorder() const {
    return true;
}

bool EnvBorder::operator==(const CompleteEnv &other) const {
    return false; // todo
}

std::unique_ptr<Prop> EnvBorder::generateProp(const sf::Vector2f &propCoords) const {
    return nullptr; // todo
}

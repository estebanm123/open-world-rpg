

#include "EnvBorder.h"

bool EnvBorder::isBorder() const {
    return true;
}

bool EnvBorder::operator==(const CompleteEnv &other) const {
    return false; // todo
}

std::unique_ptr<InteractiveProp> EnvBorder::generateInteractiveProp(const sf::Vector2f &propCoords) const {
    return nullptr; // todo
}

std::unique_ptr<DecorProp> EnvBorder::generateDecorProp(const sf::Vector2f &propCoords) const {
    return nullptr;//todo
}

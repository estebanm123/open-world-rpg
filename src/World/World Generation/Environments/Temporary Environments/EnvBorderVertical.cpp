
#include <iostream>
#include "EnvBorderVertical.h"

#include "EnvWrapper.h"
#include "../CompleteEnv.h"
#include "EnvBorderCorner.h"

EnvBorderVertical::EnvBorderVertical(const std::shared_ptr<EnvWrapper> &primary,
                                     const std::shared_ptr<EnvWrapper> &secondary) : EnvBorderData(
        primary, secondary) {}

NeighboredEnv::Neighbors EnvBorderVertical::getCompatibleNeighbors(const sf::Vector2i &direction) const {
    if (direction == constants::NORTH) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderVertical>(*this),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 270),
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 180)
        };
    }

    if (direction == constants::SOUTH) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderVertical>(*this),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 0),
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 90)
        };
    }

    if (direction == constants::WEST) {
        return NeighboredEnv::Neighbors{
                primaryEnv,
                std::make_unique<EnvBorderVertical>(nullptr, primaryEnv),
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 0),
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 270),
        };
    }

    if (direction == constants::EAST) {
        return NeighboredEnv::Neighbors{
                secondaryEnv,
                std::make_unique<EnvBorderVertical>(secondaryEnv, nullptr),
                std::make_unique<EnvBorderCorner>(secondaryEnv, nullptr, 90),
                std::make_unique<EnvBorderCorner>(secondaryEnv, nullptr, 180),
        };
    }

    return {};
}

bool EnvBorderVertical::handleEquality(const std::shared_ptr<NeighboredEnv> &other) {
    auto otherSameType = dynamic_cast<EnvBorderVertical *>(other.get());
    if (otherSameType == nullptr) return false;
    return EnvBorderData::handleEquality(std::make_shared<EnvBorderVertical>(*otherSameType));
}

std::string EnvBorderVertical::toString() const {
    return "V";
}

float EnvBorderVertical::getExtraRotationAngle() const {
    return 270; // Standardized so the default split border is horizontal w/ primary as top
}


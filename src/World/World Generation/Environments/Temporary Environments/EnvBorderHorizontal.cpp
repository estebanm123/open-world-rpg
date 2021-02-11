
#include <iostream>
#include "EnvBorderHorizontal.h"
#include "EnvBorderCorner.h"
#include "EnvWrapper.h"
#include "../CompleteEnv.h"


EnvBorderHorizontal::EnvBorderHorizontal(const std::shared_ptr<EnvWrapper> &primary,
                                         const std::shared_ptr<EnvWrapper> &secondary)
        : EnvBorderData(
        primary, secondary) {}

NeighboredEnv::Neighbors EnvBorderHorizontal::getCompatibleNeighbors(const sf::Vector2i &direction) const {
    if (direction == constants::NORTH) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderHorizontal>(nullptr, primaryEnv),
                primaryEnv,
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 0),
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 90)
        };
    }

    if (direction == constants::SOUTH) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderHorizontal>(secondaryEnv, nullptr),
                secondaryEnv,
                std::make_unique<EnvBorderCorner>(secondaryEnv, nullptr, 180),
                std::make_unique<EnvBorderCorner>(secondaryEnv, nullptr, 270)
        };
    }

    if (direction == constants::EAST) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderHorizontal>(*this),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 0),
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 270)
        };
    }

    if (direction == constants::WEST) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderHorizontal>(*this),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 90),
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 180)
        };
    }

    return {};
}

bool EnvBorderHorizontal::handleEquality(const std::shared_ptr<NeighboredEnv> &other) {
    auto otherSameType = dynamic_cast<EnvBorderHorizontal *>(other.get());
    if (otherSameType == nullptr) return false;
    return EnvBorderData::handleEquality(std::make_shared<EnvBorderHorizontal>(*otherSameType));
}

std::string EnvBorderHorizontal::toString() const {
    return "H";
}

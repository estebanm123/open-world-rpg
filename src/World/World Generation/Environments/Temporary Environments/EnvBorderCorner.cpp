
#include <iostream>
#include "EnvBorderCorner.h"
#include "EnvWrapper.h"
#include "EnvBorderVertical.h"
#include "EnvBorderHorizontal.h"
#include "../Env.h"

EnvBorderCorner::EnvBorderCorner(const std::shared_ptr<EnvWrapper> &primary,
                                 const std::shared_ptr<EnvWrapper> &secondary, float rotationAngle)
        : EnvBorderData(primary,
                        secondary),
          rotationAngle(rotationAngle) {

}

NeighboredEnv::Neighbors EnvBorderCorner::getCompatibleNeighbors(const sf::Vector2i &direction) const {
    if (direction == constants::NORTH) {
        return getNorthNeighbors();
    }

    if (direction == constants::SOUTH) {
        return getSouthNeighbors();
    }

    if (direction == constants::EAST) {
        return getEastNeighbors();
    }

    if (direction == constants::WEST) {
        return getWestNeighbors();
    }

    return {};
}

NeighboredEnv::Neighbors EnvBorderCorner::getNorthNeighbors() const {
    if (rotationAngle == 270 || rotationAngle == 180) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 90),
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 0),
                primaryEnv,
                std::make_unique<EnvBorderHorizontal>(nullptr, primaryEnv),
        };
    }
    if (rotationAngle == 0) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 270),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 180),
                std::make_unique<EnvBorderVertical>(secondaryEnv, primaryEnv),
        };
    }
    if (rotationAngle == 90) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 180),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 270),
                std::make_unique<EnvBorderVertical>(primaryEnv, secondaryEnv)
        };
    }
    return {};
}

NeighboredEnv::Neighbors EnvBorderCorner::getSouthNeighbors() const {
    if (rotationAngle == 0 || rotationAngle == 90) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 270),
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 180),
                primaryEnv,
                std::make_unique<EnvBorderHorizontal>(primaryEnv, nullptr),
        };
    }
    if (rotationAngle == 180) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 90),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 0),
                std::make_unique<EnvBorderVertical>(primaryEnv, secondaryEnv),
        };
    }
    if (rotationAngle == 270) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 0),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 90),
                std::make_unique<EnvBorderVertical>(secondaryEnv, primaryEnv)
        };
    }
    return {};
}

NeighboredEnv::Neighbors EnvBorderCorner::getWestNeighbors() const {
    if (rotationAngle == 90 || rotationAngle == 180) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 270),
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 0),
                primaryEnv,
                std::make_unique<EnvBorderVertical>(nullptr, primaryEnv),
        };
    }
    if (rotationAngle == 0) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 90),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 180),
                std::make_unique<EnvBorderHorizontal>(secondaryEnv, primaryEnv),
        };
    }
    if (rotationAngle == 270) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 180),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 90),
                std::make_unique<EnvBorderHorizontal>(primaryEnv, secondaryEnv),
        };
    }
    return {};
}

NeighboredEnv::Neighbors EnvBorderCorner::getEastNeighbors() const {
    if (rotationAngle == 0 || rotationAngle == 270) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 180),
                std::make_unique<EnvBorderCorner>(primaryEnv, nullptr, 90),
                primaryEnv,
                std::make_unique<EnvBorderVertical>(nullptr, primaryEnv),
        };
    }
    if (rotationAngle == 90) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 0),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 270),
                std::make_unique<EnvBorderHorizontal>(secondaryEnv, primaryEnv),
        };
    }
    if (rotationAngle == 180) {
        return NeighboredEnv::Neighbors{
                std::make_unique<EnvBorderCorner>(primaryEnv, secondaryEnv, 270),
                std::make_unique<EnvBorderCorner>(secondaryEnv, primaryEnv, 0),
                std::make_unique<EnvBorderHorizontal>(primaryEnv, secondaryEnv),
        };
    }
    return {};
}

bool EnvBorderCorner::handleEquality(const std::shared_ptr<NeighboredEnv> &other) {
    auto otherSameType = dynamic_cast<EnvBorderCorner *>(other.get());
    if (otherSameType == nullptr || otherSameType->rotationAngle != this->rotationAngle) return false;
    return EnvBorderData::handleEquality(std::make_shared<EnvBorderCorner>(*otherSameType));
}

bool EnvBorderCorner::operator==(const NeighboredEnv &other) const {
    try {
        const auto &o = dynamic_cast<const EnvBorderCorner &>(other);
        return o.rotationAngle == rotationAngle && EnvBorderData::operator==(other);
    } catch (const std::bad_cast &e) {
        return false;
    }
}

std::string EnvBorderCorner::toString() const {
    return "C" + std::to_string(static_cast<int>(rotationAngle));
}

float EnvBorderCorner::getExtraRotationAngle() const {
    return rotationAngle;
}

const SingleTileContainer *EnvBorderCorner::getTileContainer(const Env *primary, const Env *secondary) const {
    return primary->getCornerTileContainer(secondary);
}



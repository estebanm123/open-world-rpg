
#include "EnvWrapper.h"
#include "EnvBorderVertical.h"
#include "EnvBorderHorizontal.h"
#include "EnvBorderCorner.h"
#include "../Env.h"
#include "../EnvProxy.h"

NeighboredEnv::Neighbors EnvWrapper::getCompatibleNeighbors(const sf::Vector2i &direction) const {
    const auto currentEnv = std::make_shared<EnvWrapper>(*this);

    if (direction == constants::NORTH) {
        return NeighboredEnv::Neighbors{
                currentEnv,
                std::make_unique<EnvBorderHorizontal>(nullptr, currentEnv),
                std::make_unique<EnvBorderCorner>(currentEnv, nullptr, 0),
                std::make_unique<EnvBorderCorner>(currentEnv, nullptr, 90),
        };
    }

    if (direction == constants::SOUTH) {
        return NeighboredEnv::Neighbors{
                currentEnv,
                std::make_unique<EnvBorderHorizontal>(currentEnv, nullptr),
                std::make_unique<EnvBorderCorner>(currentEnv, nullptr, 180),
                std::make_unique<EnvBorderCorner>(currentEnv, nullptr, 270),
        };
    }

    if (direction == constants::WEST) {
        return NeighboredEnv::Neighbors{
                currentEnv,
                std::make_unique<EnvBorderVertical>(nullptr, currentEnv),
                std::make_unique<EnvBorderCorner>(currentEnv, nullptr, 0),
                std::make_unique<EnvBorderCorner>(currentEnv, nullptr, 270),
        };
    }

    if (direction == constants::EAST) {
        return NeighboredEnv::Neighbors{
                currentEnv,
                std::make_unique<EnvBorderVertical>(currentEnv, nullptr),
                std::make_unique<EnvBorderCorner>(currentEnv, nullptr, 90),
                std::make_unique<EnvBorderCorner>(currentEnv, nullptr, 180),
        };
    }

    return {};
}

EnvWrapper::EnvWrapper(const Env *env) : env(env) {}

bool EnvWrapper::operator==(const NeighboredEnv &other) const {
    try {
        const auto &o = dynamic_cast<const EnvWrapper &>(other);
        return o.env == env;
    } catch (const std::bad_cast &e) {
        return false;
    }
}

bool EnvWrapper::handleEquality(const std::shared_ptr<NeighboredEnv> &other) {
    try {
        const auto &otherSameType = dynamic_cast<const EnvWrapper *>(other.get());
        if (otherSameType == nullptr) return false;
        return otherSameType->env == this->env;
    } catch (const std::bad_cast &e) {
        return false;
    }
}

std::string EnvWrapper::toString() const {
    return "E";
}

bool EnvWrapper::fillWildcardIfExists(const std::shared_ptr<EnvWrapper> &filler) {
    return false;
}

const NeighboredEnv::TileContainerWrapper EnvWrapper::extractTileMetadata(const sf::Vector2f &globalCoords) const {
    const auto &tileContainer = env->selectTileContainer(globalCoords);
    Tile::Metadata metadata{std::make_unique<const EnvProxy>(env), globalCoords,
                            env->getSpriteSheetPath()};
    return {std::move(metadata), tileContainer};
}

const Env *EnvWrapper::getEnv() const {
    return env;
}

std::pair<const Env *, const Env *> EnvWrapper::getEnvs() const {
   return std::make_pair(env, nullptr);
}








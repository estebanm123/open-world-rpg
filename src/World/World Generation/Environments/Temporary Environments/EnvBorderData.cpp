

#include "EnvBorderData.h"
#include "EnvWrapper.h"
#include "../EnvBorder.h"
#include "../Env.h"
#include "../../Tiles/TileContainers/SingleTileContainer.h"
#include <utility>


EnvBorderData::EnvBorderData(const std::shared_ptr<EnvWrapper> &primary, const std::shared_ptr<EnvWrapper> &secondary)
        : primaryEnv(
        primary),
          secondaryEnv(
                  secondary) {
}

bool EnvBorderData::handleEquality(const std::shared_ptr<NeighboredEnv> &other) {
    if (other == nullptr) return false;
    const auto &otherBorder = dynamic_cast<EnvBorderData *>(other.get());
    if (this->secondaryEnv == nullptr) {
        this->secondaryEnv = otherBorder->secondaryEnv;
    }

    if (this->primaryEnv == nullptr) {
        this->primaryEnv = otherBorder->primaryEnv;
    }

    bool primaryAreEqual =
            otherBorder->primaryEnv == nullptr || otherBorder->primaryEnv->handleEquality(this->primaryEnv);
    bool secondaryAreEqual =
            otherBorder->secondaryEnv == nullptr || otherBorder->secondaryEnv->handleEquality(this->secondaryEnv);
    return primaryAreEqual && secondaryAreEqual;
}

bool EnvBorderData::operator==(const NeighboredEnv &other) const {
    try {
        const auto &o = dynamic_cast<const EnvBorderData &>(other);

        return o.primaryEnv->handleEquality(primaryEnv) && o.secondaryEnv->handleEquality(secondaryEnv);
    } catch (const std::bad_cast &e) {
        return false;
    }
}

bool EnvBorderData::fillWildcardIfExists(const std::shared_ptr<EnvWrapper> &filler) {
    if (primaryEnv == nullptr) {
        if (secondaryEnv == nullptr || !(*secondaryEnv == *filler)) {
            primaryEnv = filler;
            return true;
        }
    } else if (secondaryEnv == nullptr) {
        if (primaryEnv == nullptr || !(*primaryEnv == *filler)) {
            secondaryEnv = filler;
            return true;
        }
    }

    return false;
}

float EnvBorderData::getExtraRotationAngle() const {
    return 0;
}

const NeighboredEnv::TileContainerWrapper EnvBorderData::extractTileMetadata(const sf::Vector2f &globalCoords) const {
    auto firstEnv = primaryEnv->getEnv();
    auto secondEnv = secondaryEnv->getEnv();
    const TileContainer *tileContainer = getTileContainer(firstEnv, secondEnv);
    auto selectedEnv = firstEnv;
    auto rotationAngle = getExtraRotationAngle();
    if (!tileContainer) {
        tileContainer = getTileContainer(secondEnv, firstEnv);
        selectedEnv = secondEnv;
        if (!tileContainer)
            throw std::runtime_error(
                    "No border tile container found in either env - you probably forgot to allocate one");
        rotationAngle += 180;
    }
    const auto &spriteSheetPath = selectedEnv->getSpriteSheetPath();
    EnvBorder placeholder;
    const auto simplifiedAngle = static_cast<float>(static_cast<int>(rotationAngle) % 360);
    Tile::Metadata metadata{std::make_shared<CompleteEnv>(placeholder), globalCoords, spriteSheetPath,
                            simplifiedAngle}; // EnvBorder is placeholder
    return {metadata, tileContainer};
}

const TileContainer *EnvBorderData::getTileContainer(const Env *primary, const Env *secondary) const {
    return primary->getSplitTileContainer(secondary);
}




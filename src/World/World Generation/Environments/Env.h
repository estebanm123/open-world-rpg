#pragma once

#include "CompleteEnv.h"
#include "../../../Util/Constants.h"
#include <unordered_map>
#include <SFML/System/NonCopyable.hpp>
#include "../Tiles/TileContainer.h"
#include "../../../Util/NonMoveable.h"

class SingleTileContainer;

class EnvWrapper;

class Env : public CompleteEnv, sf::NonCopyable, NonMoveable {
public:
    static inline std::string TILE_SHEET_PATH = "Levels/tiles";

    typedef std::unordered_map<const Env *, std::vector<std::shared_ptr<SingleTileContainer>>> BorderTileContainers;

    struct Config {
        Config() {};
        std::string spriteSheet = TILE_SHEET_PATH;
        int multiTileIndex = -1;
    };

    const std::string &getSpriteSheetPath() const;

    void setBorderTileContainers(const BorderTileContainers & splits, const BorderTileContainers & corners);

    // Could return null if there is no associated border tile container
    SingleTileContainer * getSplitTileContainer(const Env *) const;
    SingleTileContainer * getCornerTileContainer(const Env *) const;

    explicit Env(const TileContainer::TileContainers &completeTileContainers, struct Config config={});

    TileContainer * selectTileContainer(const sf::Vector2f &coords) const;

    std::shared_ptr<EnvWrapper> extractEnvWrapper() const;

private:
    const int multiTileIndex;
    TileContainer::TileContainers completeTileContainers;
    BorderTileContainers splitBorderTileContainers;
    BorderTileContainers cornerBorderTileContainers;
    const std::string spriteSheet;
};


#pragma once

#include "CompleteEnv.h"
#include "../../../Util/Constants.h"
#include <unordered_map>
#include <SFML/System/NonCopyable.hpp>
#include "../Tiles/TileContainers/TileContainer.h"
#include "../../../Util/NonMoveable.h"
#include "../../Entities/Collidables/Props/Prop Factories/PropFactory.h"

class SingleTileContainer;

class Prop;

class EnvWrapper;

class Env : public CompleteEnv, sf::NonCopyable, NonMoveable {
public:
    static inline std::string TILE_SHEET_PATH = "Tiles/tiles";

    typedef std::unordered_map<const Env *, std::vector<std::shared_ptr<TileContainer>>> BorderTileContainers;

    struct Config {
        explicit Config(PropFactory *propFactory) : propFactory(propFactory) {};

        Config() {};
        std::string spriteSheet = TILE_SHEET_PATH;
        int multiTileIndex = -1;
        PropFactory *propFactory = nullptr;
    };

    explicit Env(TileContainer::TileContainers completeTileContainers, struct Config config = {});

    const std::string &getSpriteSheetPath() const;

    bool isBorder() const override;

    bool operator==(const CompleteEnv &other) const override;

    void setBorderTileContainers(const BorderTileContainers &splits, const BorderTileContainers &corners);

    // Could return null if there is no associated border tile container
    TileContainer *getSplitTileContainer(const Env *) const;

    TileContainer *getCornerTileContainer(const Env *) const;

    TileContainer *selectTileContainer(const sf::Vector2f &coords) const;

    std::unique_ptr<Prop> generateProp(const sf::Vector2f &propCoords, bool isDecor) const override;

private:
    const int multiTileIndex;
    TileContainer::TileContainers completeTileContainers;
    BorderTileContainers splitBorderTileContainers;
    BorderTileContainers cornerBorderTileContainers;
    PropFactory *propFactory; // owner should be global
    const std::string spriteSheet;
};


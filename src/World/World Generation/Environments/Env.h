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

class EnvNeighborInfo;

class Env : public CompleteEnv, sf::NonCopyable, NonMoveable {
public:
    typedef std::unordered_map<const Env *, TileContainer::TileContainers> BorderTileContainers;

    typedef int EnvId;

    struct Config {
        Config(EnvId id, std::string spriteSheet, int numFullTiles, std::vector<EnvNeighborInfo> borderData,
               std::unique_ptr<PropFactory> propFactory = nullptr,
               std::unique_ptr<Animation::BaseMetadata> animMetadata = nullptr
        );

        EnvId id;
        std::string spriteSheet;
        int numFullTiles;
        std::vector<EnvNeighborInfo> borderDataCollection;
        //        int multiTileIndex = -1;
        std::unique_ptr<PropFactory> propFactory;
        std::unique_ptr<Animation::BaseMetadata> animMetadata;
    };

    explicit Env(std::unique_ptr<Config> config);

    const std::string &getSpriteSheetPath() const;

    bool operator==(const CompleteEnv &other) const;

    void setBorderTileContainers(const BorderTileContainers &splits, const BorderTileContainers &corners);

    // Could return null if there is no associated border tile container
    TileContainer *getSplitTileContainer(const Env *) const;

    TileContainer *getCornerTileContainer(const Env *) const;

    TileContainer *selectTileContainer(const sf::Vector2f &coords) const;

    std::unique_ptr<Prop> generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const override;

    void setPropFactory(std::unique_ptr<PropFactory> propFactory);

    void setSpriteSheet(std::string spriteSheet);

    void setCompleteTileContainers(const TileContainer::TileContainers & completeTileContainers);

    Config * getConfig();


private:
//    const int multiTileIndex;
    TileContainer::TileContainers completeTileContainers;
    BorderTileContainers splitBorderTileContainers;
    BorderTileContainers cornerBorderTileContainers;
    std::unique_ptr<PropFactory> propFactory;
    std::string spriteSheet;
    std::unique_ptr<Config> tempConfig;
};


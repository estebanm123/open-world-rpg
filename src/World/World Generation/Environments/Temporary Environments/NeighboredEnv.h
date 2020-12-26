#pragma once

#include <memory>
#include <vector>
#include "../../../../Util/NonMoveable.h"
#include "../../Tiles/Tile.h"

class EnvWrapper;

class CompleteEnv;

class TileContainer;

class NeighboredEnv {
public:
    typedef std::vector<std::shared_ptr<NeighboredEnv>> Neighbors;

    struct TileContainerWrapper {
        TileContainerWrapper(const struct Tile::Metadata &metadata, const TileContainer *tileContainer) : metadata(
                metadata), tileContainer(tileContainer) {};
        struct Tile::Metadata metadata;
        const TileContainer *tileContainer;
    };

    virtual const TileContainerWrapper extractTileMetadata(const sf::Vector2f &globalCoords) const = 0;

    virtual Neighbors getCompatibleNeighbors(const sf::Vector2i &direction) const = 0;

    // Alternative to overload boolean== as it can modify this object if it contains 'wildcard'
    // fields (nullptrs)
    virtual bool handleEquality(const std::shared_ptr<NeighboredEnv> &other) = 0;

    virtual bool operator==(const NeighboredEnv &other) const = 0;

    virtual std::string toString() const = 0;

    // Returns true upon success.
    virtual bool fillWildcardIfExists(const std::shared_ptr<EnvWrapper> &filler) = 0;

    bool isPriorityEnv() const;

    void togglePriority();

    virtual ~NeighboredEnv() = default;

private:
    bool isPriority = false;
};



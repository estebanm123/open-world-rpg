#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include "../Tiles/TileMap.h"
#include "../Tiles/Tile.h"


class Tile;

class Prop;


class ChunkPropGenerator {
public:
    static std::unordered_set<std::unique_ptr<Prop>> generateProps(const TileMap &tileMap);

private:
    typedef std::array<std::array<bool, TileMap::SIZE_X>, TileMap::SIZE_Y> TilesSeen;

    static ChunkPropGenerator::TilesSeen initializeTilesSeen();

    static void updateCurrentPropChanceOnFailure(float &currentChance);

    static void updateCurrentPropChanceOnSuccess(float &currentChance);

    static bool validateProp(Prop *generatedProp, const TileMap &tiles, TilesSeen &tilesSeen,
                             const sf::Vector2i &localCoords);

    static int hashTileCoords(Tile &tile);


    static constexpr float PROP_CHANCE_MAX = 100;
    static constexpr float PROP_CHANCE = 80;
    static constexpr float PROP_CHANCE_CHANGE = 3;
};


#include "Decor/DecorProp.h"
#include "Interactive/InteractiveProp.h"
#include "ChunkPropGenerator.h"
#include "../Tiles/TileMap.h"
#include "../Tiles/Tile.h"
#include "../../../Util/Random/Hash.h"
#include "../../../World/World Generation/Environments/Env.h"

typedef std::array<std::array<bool, TileMap::SIZE_X>, TileMap::SIZE_Y> TilesSeen;

TilesSeen initializeTilesSeen() {
    TilesSeen tilesSeen;
    for (auto &row : tilesSeen) {
        for (auto &marker : row) {
            marker = false;
        }
    }
    return tilesSeen;
}

sf::Vector2f generatePropCoords(float propGenChance, int hashVal1) {
    using namespace worldConstants;
    auto hashVal2 = hashCoords(hashVal1, static_cast<int>(propGenChance));
    int limit = static_cast<int>(propGenChance);
    auto x = static_cast<float>((limit * hashVal2) % TILE_SIZE_INT_X);
    auto y = static_cast<float>((limit * hashVal1) % TILE_SIZE_INT_Y);
    return {x, y};
}

std::vector<std::unique_ptr<InteractiveProp>> ChunkPropGenerator::generateInteractiveProps(const TileMap &tileMap) {
    // todo: find a nice way to reduce code duplication w/ generateDecorProps

    std::vector<std::unique_ptr<InteractiveProp>> props;

    auto currentPropChance = PROP_CHANCE;
    TilesSeen tilesSeen = initializeTilesSeen();

    for (int x = 0; x < TileMap::SIZE_X; x++) {
        for (int y = 0; y < TileMap::SIZE_Y; y++) {
            auto &curTile = tileMap.tiles[x][y];
            auto curEnv = curTile->getEnvironment();
            auto pos = curTile->getPosition();
            auto tileCoordHash = hashCoordsWithSize(pos.x, pos.y, PROP_CHANCE_MAX);
            if (tileCoordHash > currentPropChance) {
                auto propCoords = generatePropCoords(currentPropChance, tileCoordHash);
                auto prop = curEnv->generateInteractiveProp(propCoords);
                if (prop == nullptr) {
                    // water or border tile
                    continue;
                }
                currentPropChance += PROP_CHANCE_CHANGE;
                props.push_back(prop);
            } else {
                if (currentPropChance + PROP_CHANCE_CHANGE < PROP_CHANCE_MAX) {
                    currentPropChance -= PROP_CHANCE_CHANGE;
                }
            }
        }
    }

    return props;
}

std::vector<std::unique_ptr<DecorProp>> ChunkPropGenerator::generateDecorProps(const TileMap &tileMap) {
}


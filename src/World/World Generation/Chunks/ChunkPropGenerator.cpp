#include "ChunkPropGenerator.h"
#include "../../../Util/Random/Hash.h"
#include "../Environments/Env.h"
#include "../../Entities/Collidables/Props/Prop.h"


ChunkPropGenerator::TilesSeen ChunkPropGenerator::initializeTilesSeen() {
    TilesSeen tilesSeen;
    for (auto &row : tilesSeen) {
        for (auto &marker : row) {
            marker = false;
        }
    }
    return tilesSeen;
}


sf::Vector2f generatePropCoords(float propGenChance, int hashVal1, const sf::Vector2f &tileGlobalCoords) {
    using namespace worldConstants;
    auto hashVal2 = hashCoords(hashVal1, static_cast<int>(propGenChance));
    int limit = static_cast<int>(propGenChance);
    auto x = static_cast<float>(hashVal2 % TILE_SIZE_INT_X);
    auto y = static_cast<float>((limit * hashVal1) % TILE_SIZE_INT_Y);
    return {x + tileGlobalCoords.x, y + tileGlobalCoords.y};
}

std::unordered_set<std::unique_ptr<Prop>> ChunkPropGenerator::generateProps(TileMap &tileMap, bool isDecor) {
    std::unordered_set<std::unique_ptr<Prop>> props;
    auto currentPropChance = PROP_CHANCE;
    TilesSeen tilesSeen = initializeTilesSeen();

    for (int x = 0; x < TileMap::SIZE_X; x++) {
        for (int y = 0; y < TileMap::SIZE_Y; y++) {
            auto curTile = tileMap.getTile(x, y);
            auto curEnv = curTile->getEnvironment();
            auto tileCoordHash = hashTileCoords(*curTile) ^static_cast<int>(currentPropChance);
            if (tileCoordHash > currentPropChance) {
                auto propCoords = generatePropCoords(currentPropChance, tileCoordHash, curTile->getPosition());
                auto prop = curEnv->generateProp(propCoords, isDecor);
                if (!validateProp(prop.get(), tileMap, tilesSeen, {x, y}, isDecor)) {
                    continue;
                }
                updateCurrentPropChanceOnSuccess(currentPropChance);
                props.insert(std::move(prop));
            } else {
                updateCurrentPropChanceOnFailure(currentPropChance);
            }
        }
    }

    return props;
}

void ChunkPropGenerator::updateCurrentPropChanceOnFailure(float &currentChance) {
    currentChance += PROP_CHANCE_CHANGE;
}

void ChunkPropGenerator::updateCurrentPropChanceOnSuccess(float &currentChance) {
    if (currentChance + PROP_CHANCE_CHANGE < PROP_CHANCE_MAX) {
        currentChance -= PROP_CHANCE_CHANGE;
    }
}

bool ChunkPropGenerator::validateProp(Prop *prop, const TileMap &tiles, TilesSeen &tilesSeen,
                                      const sf::Vector2i &localCoords, bool isDecor) {
    if (!prop) return false;
    if (isDecor) return true;
    return !tiles.isEntityCrossingBounds(prop);
}

int ChunkPropGenerator::hashTileCoords(Tile &tile) {
    auto pos = tile.getPosition();
    auto tileCoordHash = hash2ValuesModSize(pos.x, pos.y, static_cast<int>(PROP_CHANCE_MAX)); // never more than 1000
    return tileCoordHash;
}




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
    auto hashVal2 = mixCoords(hashVal1, static_cast<int>(propGenChance));
    int limit = static_cast<int>(propGenChance);
    auto x = static_cast<float>(hashVal2 % TILE_SIZE_INT_X);
    auto y = static_cast<float>((limit * hashVal1) % TILE_SIZE_INT_Y);
    return {x + tileGlobalCoords.x, y + tileGlobalCoords.y};
}

std::unordered_set<std::unique_ptr<Prop>>
ChunkPropGenerator::generateEnvironmentalProps(TileMap &tileMap, bool isDecor) {
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
                auto prop = curEnv->generateEnvironmentalProp(propCoords, isDecor);
                if (!isPropValid(prop.get(), tileMap, tilesSeen, {x, y}, isDecor)) {
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

// Divisor used against prop's max length (width/height) - a larger value = less safe but more natural results
constexpr auto PROP_COLLISION_LENIENCY_FACTOR = 3;

// Marks prop as seen
// Extra safe (a little inaccurate)
bool
ChunkPropGenerator::isPropOverlappingOthersAndMarkAsSeen(Prop *prop, const sf::Vector2i &localCoords,
                                                         TilesSeen &tilesSeen,
                                                         const TileMap &tiles) {
    auto entitySize = prop->getSize();
    auto &entityPos = prop->getPosition();
    auto entityMaxLen = std::max(entitySize.y, entitySize.x) / PROP_COLLISION_LENIENCY_FACTOR; // take max to be safe; entity could be rotated

    auto southEntityLim = tiles.convertGlobalToLocalCoords({entityPos.x, entityPos.y + entityMaxLen}).y;
    auto eastEntityLim = tiles.convertGlobalToLocalCoords({entityPos.x + entityMaxLen, entityPos.y}).x;
    auto northEntityLim = tiles.convertGlobalToLocalCoords({entityPos.x, entityPos.y - entityMaxLen}).y;
    auto westEntityLim = tiles.convertGlobalToLocalCoords({entityPos.x - entityMaxLen, entityPos.y}).x;

    bool isOverlapping = tilesSeen[localCoords.x][localCoords.y] || tilesSeen[localCoords.x][southEntityLim] ||
                         tilesSeen[localCoords.x][northEntityLim] || tilesSeen[westEntityLim][localCoords.y] ||
                         tilesSeen[eastEntityLim][localCoords.y];
    if (isOverlapping) return true;
    tilesSeen[localCoords.x][localCoords.y] = true;
    tilesSeen[localCoords.x][southEntityLim] = true;
    tilesSeen[localCoords.x][northEntityLim] = true;
    tilesSeen[westEntityLim][localCoords.y] = true;
    tilesSeen[eastEntityLim][localCoords.y] = true;
    return false;
}

bool ChunkPropGenerator::isPropValid(Prop *prop, const TileMap &tiles, TilesSeen &tilesSeen,
                                     const sf::Vector2i &localCoords, bool isDecor) {
    if (!prop) return false;
    if (isDecor) return true;

    return !tiles.isEntityCrossingBounds(prop) &&
           !isPropOverlappingOthersAndMarkAsSeen(prop, localCoords, tilesSeen, tiles);
}

int ChunkPropGenerator::hashTileCoords(Tile &tile) {
    auto pos = tile.getPosition();
    auto tileCoordHash = hash2ValuesModSize(pos.x, pos.y, static_cast<int>(PROP_CHANCE_MAX)); // never more than 1000
    return tileCoordHash;
}





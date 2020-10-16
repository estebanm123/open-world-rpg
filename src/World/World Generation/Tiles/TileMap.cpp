#include "TileMap.h"

#include "../../../Resource Managers/ResourceHolder.h"
#include "../../../Util/Constants.h"

// Creates a tilemap for rendering purposes.
// ctor used primarily for chunks - where pos is based on chunk center
// since pos corresponds to top left corner - a shift is performed to accommodate for chunk center
TileMap::TileMap(sf::Vector2f pos, sf::Vector2i size) : pos(pos - worldConstants::CHUNK_SIZE / 2.f)
{
    for (int x = 0; x < size.y; x++) {
        for (int y = 0; y < size.y; y++) {
            sf::Vector2i coords {x,y};
            // get neighbors - maybe refactor to shared ptr?? so we can set as null
            // then pass all to tilegenerator 
        }
    }
}

void TileMap::renderBy(sf::RenderTarget& target) const
{
    for (Tile tile : tiles) {
        tile.renderBy(target);
    }
}


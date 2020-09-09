#include "TileMap.h"

#include "../../ResourceManagers/ResourceHolder.h"
#include "../../Util/Constants.h"

// ctor used primarily for chunks - where pos is based on chunk center
// since pos corresponds to top left corner - a shift is performed to accomodate for chunk center
TileMap::TileMap(sf::Vector2f pos, const std::string& tileSetSheet, sf::Vector2u tileSize, const std::vector<char>& tiles, float width, float height)
     :  tileSet(ResourceHolder::get().textures.get(tileSetSheet)), pos(pos - worldConstants::CHUNK_SIZE / 2.f)
{
   
   // tileSet = ResourceHolder::get().textures.get(tileSetSheet);
	
    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (auto i = 0; i < width; ++i)
        for (auto j = 0; j < height; ++j)
        {
            // get the current tile type
            auto tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            auto tu = tileNumber % (tileSet.getSize().x / tileSize.x);
            auto tv = tileNumber / (tileSet.getSize().x / tileSize.x);

            // get address to override vertices field w/ tile corners
            sf::Vertex* quad = &vertices[(i + j * width) * 4];

        	// set position
            quad[0].position = this->pos + sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = this->pos + sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = this->pos + sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = this->pos + sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
}

void TileMap::renderBy(sf::RenderTarget& target) const
{
    target.draw(*this);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileSet;
    target.draw(vertices, states);
}

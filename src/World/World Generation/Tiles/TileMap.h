#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <array>
#include <memory>
#include "../../../Util/Constants.h"

class Tile;

class TileMap {
public:
    explicit TileMap(sf::Vector2f pos);

    void renderBy(sf::RenderTarget &target);

    constexpr static int SIZE_X = worldConstants::TILES_PER_CHUNK_X;
    constexpr static int SIZE_Y = worldConstants::TILES_PER_CHUNK_Y;

    typedef std::array<std::array<std::unique_ptr<Tile>, TileMap::SIZE_Y>, TileMap::SIZE_X> Tiles;

    static sf::Vector2f convertLocalToGlobalCoords(sf::Vector2i localCoords, sf::Vector2f globalPos);

private:
    Tiles tiles;
    sf::Vector2f pos;

};
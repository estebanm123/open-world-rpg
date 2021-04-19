#pragma once

#include <SFML/System/Vector2.hpp>
#include <array>
#include <string>

namespace constants {
    const inline sf::Vector2i NORTH = {0, 1};
    const inline sf::Vector2i CENTER = {0, 0};
    const inline sf::Vector2i SOUTH = {0, -1};
    const inline sf::Vector2i WEST = {-1, 0};
    const inline sf::Vector2i EAST = {1, 0};
    const inline sf::Vector2i NORTH_WEST = {-1, 1};
    const inline sf::Vector2i NORTH_EAST = {1, 1};
    const inline sf::Vector2i SOUTH_WEST = {-1, -1};
    const inline sf::Vector2i SOUTH_EAST = {1, -1};

    const inline int HASH_PRIME = 31;
}

using namespace constants;
const inline std::array<sf::Vector2i, 9> directions{
        CENTER,
        NORTH,
        NORTH_EAST,
        NORTH_WEST,
        SOUTH_EAST,
        SOUTH,
        SOUTH_WEST,
        EAST,
        WEST,
};

namespace worldConstants {

    constexpr inline int TILES_PER_CHUNK_X = 12;
    constexpr inline int TILES_PER_CHUNK_Y = 12;

    const inline sf::Vector2f TILE_SIZE = {48, 48}; // (all sizes in pixels)
    const inline int TILE_SIZE_INT_X = static_cast<int>(TILE_SIZE.x);
    const inline int TILE_SIZE_INT_Y = static_cast<int>(TILE_SIZE.y);
    const inline sf::Vector2f TILES_PER_CHUNK = {TILES_PER_CHUNK_X, TILES_PER_CHUNK_Y};
    const inline sf::Vector2f CHUNK_SIZE = {TILE_SIZE.x * TILES_PER_CHUNK.x, TILE_SIZE.y * TILES_PER_CHUNK.y};
    const inline sf::Vector2f INITIAL_PLAYER_POS = {10000, 303000};
}

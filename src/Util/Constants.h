﻿#pragma once

#include <SFML/System/Vector2.hpp>

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
}

using namespace constants;
const inline std::array<sf::Vector2i, 9> directions{{
                                                            CENTER,
                                                            NORTH,
                                                            NORTH_EAST,
                                                            NORTH_WEST,
                                                            SOUTH_EAST,
                                                            SOUTH,
                                                            SOUTH_WEST,
                                                            EAST,
                                                            WEST,
                                                    }};

namespace worldConstants {
    constexpr inline int TILES_PER_CHUNK_X = 32;
    constexpr inline int TILES_PER_CHUNK_Y = 32;

    const inline int NUM_TILES = 16;
    const inline sf::Vector2f TILE_SIZE = {32, 32}; // (all sizes in pixels)
    const inline sf::Vector2f TILES_PER_CHUNK = {TILES_PER_CHUNK_X, TILES_PER_CHUNK_Y};
    const inline sf::Vector2f CHUNK_SIZE = {TILE_SIZE.x * TILES_PER_CHUNK.x, TILE_SIZE.y * TILES_PER_CHUNK.y};
    const inline sf::Vector2f INITIAL_PLAYER_POS = {400, 400};
}

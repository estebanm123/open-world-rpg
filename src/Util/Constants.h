#pragma once
#include <SFML/System/Vector2.hpp>

namespace constants
{
	const static sf::Vector2i NORTH = { 0,1 };
	const static sf::Vector2i CENTER = { 0,0 };
	const static sf::Vector2i SOUTH = { 0,-1 };
	const static sf::Vector2i WEST = { -1,0 };
	const static sf::Vector2i EAST = { 1,0 };
	const static sf::Vector2i NORTH_WEST = { -1,1 };
	const static sf::Vector2i NORTH_EAST = { 1,1 };
	const static sf::Vector2i SOUTH_WEST = { -1,-1 };
	const static sf::Vector2i SOUTH_EAST = { 1,-1 };   
}

namespace worldConstants
{
	const static std::string TILE_SHEET_PATH = "Levels/tileMap";
	const static int NUM_TILES = 16;
	const static sf::Vector2u TILE_SIZE = { 32, 32 };
	const static sf::Vector2f TILES_PER_CHUNK = { 20, 20 };
	const static sf::Vector2f CHUNK_SIZE = { TILE_SIZE.x * TILES_PER_CHUNK.x, TILE_SIZE.y * TILES_PER_CHUNK.y };
	const static sf::Vector2f INITIAL_PLAYER_POS = { 400, 400 };
}

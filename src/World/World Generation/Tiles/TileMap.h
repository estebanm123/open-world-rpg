#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <array>
#include <memory>
#include <string>

#include "../../../Util/Constants.h"

class Tile;

class Entity;

class TileMap {
public:
	explicit TileMap(sf::Vector2f pos);

	void renderBy(sf::RenderTarget &target);

	constexpr static int SIZE_X = worldConstants::TILES_PER_CHUNK_X;
	constexpr static int SIZE_Y = worldConstants::TILES_PER_CHUNK_Y;

	typedef std::array<std::array<std::unique_ptr<Tile>, TileMap::SIZE_Y>, TileMap::SIZE_X> Tiles;

	const sf::Vector2f &getTopLeftPos() const;

	Tile *getTileFromGlobalCoords(sf::Vector2f globalCoords);

	// in local coords
	Tile *getTile(int x, int y);

	bool isEntityCrossingBounds(Entity *entity) const;

	sf::Vector2i convertGlobalToLocalCoords(const sf::Vector2f &globalCoords) const;

	// Global position should be the global origin of the TileMap
	static sf::Vector2f convertLocalToGlobalCoords(sf::Vector2i localCoords, sf::Vector2f globalPos);

private:
	friend class ChunkDebug;

	Tiles tiles;
	sf::Vector2f pos;  // NOTE: this is top left pos!
};
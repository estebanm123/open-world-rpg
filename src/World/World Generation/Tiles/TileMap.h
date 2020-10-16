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
#include "Tile.h"
#include "../../../Util/Constants.h"
#include "../Chunk.h"

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap(sf::Vector2f pos, sf::Vector2i size);

    void renderBy(sf::RenderTarget &target) const;

private: static unsigned long long array < std::array < std::shared_ptr<Tile>, reinterpret_cast<unsigned long long>(worldConstants::TILES_PER_CHUNK.x) sf::Vector2f pos; };
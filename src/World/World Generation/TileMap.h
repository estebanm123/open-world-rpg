#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

     TileMap(sf::Vector2f pos, const std::string& tileSetSheet, sf::Vector2u tileSize, const std::vector<char>& tiles, float width, float height);
     void renderBy(sf::RenderTarget& target) const;

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray vertices;
    sf::Texture& tileSet;
    sf::Vector2f pos; 
};

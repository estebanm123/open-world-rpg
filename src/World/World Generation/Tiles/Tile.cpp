


#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include "Tile.h"
#include "../../../Resource Managers/ResourceHolder.h"
#include "../Environments/Env.h"
#include "../../../Util/Constants.h"

void Tile::renderBy(sf::RenderTarget &renderer) const {
    renderer.draw(sprite);
}

int Tile::getLocalX() const {
    return localCoords.x;
}

int Tile::getLocalY() const {
    return localCoords.y;
}

Tile::Tile(const sf::IntRect &spriteSheetCoords, const sf::Vector2f &position, const Env &environment,
           const sf::Vector2i localCoords) : environment(environment), pos(position) {

    const auto &spriteSheetPath = environment.getSpriteSheetPath();
    sprite.setTexture(ResourceHolder::get().textures.get(spriteSheetPath));
    sprite.setTextureRect(spriteSheetCoords);

    sprite.setPosition(pos.x, pos.y);

}



#pragma once

#include <SFML/System/Vector2.hpp>

#include "Tiles/TileMap.h"

class Chunk {
public:
    struct RequestData {
        sf::Vector2i dir; // cardinal direction relative to central chunk
        sf::Vector2f pos; //  pos (center) of central chunk adjacent to it
        // neighbors
    };

    Chunk(const RequestData &reqData, TileMap tiles, const sf::Vector2f &center);

    static sf::Vector2f getCenterFromReqData(const Chunk::RequestData &data);

    const RequestData &getReqData() const;

    const sf::Vector2f &getCenter() const;

    void renderBy(sf::RenderTarget &target) const;

private:
    RequestData reqData;
    TileMap tiles;
    sf::Vector2f center; // position? origin?
    // neighbors
};

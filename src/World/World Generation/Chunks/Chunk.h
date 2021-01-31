﻿#pragma once

#include <SFML/System/Vector2.hpp>
#include <unordered_set>

#include "../Tiles/TileMap.h"
#include "ChunkCollisionHandler.h"

class Player;

class MoveableEntity;

class Prop;


class Chunk {
public:
    struct RequestData {
        sf::Vector2i dir; // cardinal direction relative to central chunk
        sf::Vector2f pos; //  pos (center) of central chunk adjacent to it
        // neighbors
    };

    struct Neighbors {
//        Neighbors(
//                std::unique_ptr<Chunk> *north,
//                std::unique_ptr<Chunk> *south,
//                std::unique_ptr<Chunk> *west,
//                std::unique_ptr<Chunk> *east
//        ) : north(north), south(south), west(west), east(east) {
//
//        }

        std::unique_ptr<Chunk> *north;
        std::unique_ptr<Chunk> *south;
        std::unique_ptr<Chunk> *west;
        std::unique_ptr<Chunk> *east;
    };

    Chunk(const RequestData &reqData, TileMap tiles, const sf::Vector2f &center,
          std::unordered_set<std::unique_ptr<Prop>> props);

    static sf::Vector2f getCenterFromReqData(const Chunk::RequestData &data);

    const RequestData &getReqData() const;

    const sf::Vector2f &getCenter() const;

    void update(float dt);

    void renderBy(sf::RenderTarget &target);

    void setNeighbors(const Neighbors & newNeighbors);

    void addMoveable(MoveableEntity *moveable, bool checkCollision = false);

private:
    typedef std::unordered_set<MoveableEntity *>::iterator MoveableIter;

    void removeMoveable(MoveableIter & it);

    friend class ChunkCollisionHandler;

    RequestData reqData;
    TileMap tiles;
    sf::Vector2f center; // position? origin?
    std::unordered_set<std::unique_ptr<Prop>> props;
    std::unordered_set<MoveableEntity *> moveableEntities;
    Neighbors neighbors;
    ChunkCollisionHandler collisionHandler;


    void updateEntities(float dt);

};
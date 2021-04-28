#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include "../../Entities/Sprites/SpriteReg.h"

class CompleteEnv;

class Tile {
public:
    struct Metadata {
        // All the data needed to extract tile(s)
        Metadata(std::unique_ptr<const CompleteEnv> completeEnv,
                 const sf::Vector2f &globalCoords, const std::string &spriteSheetPath, float rotationAngle = 0)
                : rotationAngle(rotationAngle),
                  spriteSheetPath(spriteSheetPath),
                  completeEnv(std::move(completeEnv)),
                  globalCoords(globalCoords)
        {}

        float rotationAngle;
        const std::string &spriteSheetPath;
        std::unique_ptr<const CompleteEnv> completeEnv; // Could be initialized by temp NeighboredEnv
        sf::Vector2f globalCoords;
    };

    // spritesheet path is taken from Env
    explicit Tile(Metadata metadata);

    friend class TileMap; //todo: DELETE

    virtual void renderBy(sf::RenderTarget &target);

    virtual ~Tile() = default;

    const sf::Vector2f &getTopLeftPos();

    const CompleteEnv * getEnvironment() const;

protected:
    friend class ChunkDebug;

    SpriteReg sprite;
    sf::Vector2f topLeft;
    std::unique_ptr<const CompleteEnv> env;
};





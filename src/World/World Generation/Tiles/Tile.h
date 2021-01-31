#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include "../../Entities/RegSprite.h"

class CompleteEnv;

class Tile {
public:
    struct Metadata {
        // All the data needed to extract tile(s)
        Metadata(std::shared_ptr<CompleteEnv> completeEnv,
                 const sf::Vector2f &globalCoords, const std::string &spriteSheetPath, float rotationAngle = 0)
                : rotationAngle(rotationAngle),
                  spriteSheetPath(spriteSheetPath),
                  completeEnv(std::move(completeEnv)),
                  globalCoords(globalCoords) {}

        float rotationAngle;
        const std::string &spriteSheetPath;
        const std::shared_ptr<CompleteEnv> completeEnv; // Could be initialized by temp NeighboredEnv
        sf::Vector2f globalCoords;
    };

    // spritesheet path is taken from Env
    explicit Tile(const Metadata &metadata);

    virtual void renderBy(sf::RenderTarget &target);

    virtual ~Tile() = default;

    const sf::Vector2f &getPosition();

    std::shared_ptr<CompleteEnv> getEnvironment() const;

protected:
    RegSprite sprite;
    sf::Vector2f pos;
    const std::shared_ptr<CompleteEnv> environment;
};





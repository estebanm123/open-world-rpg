#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "../Util/Random/Random.h"
#include "World Generation/Chunks/ChunkManager.h"
#include "Projectiles/Projectile.h"
#include "Weapons/ProjectileWeapon.h"
#include "../Util/Observer/Observable.h"
#include "Entities/Collidables/Organisms/Humanoid/Player/Player.h"

class World : Observable {
public:
    explicit World(std::shared_ptr<sf::View> worldView);

    void renderBy(sf::RenderTarget &renderer);

    void handleInput(sf::RenderWindow &window);

    void update(float dt);

private:
    std::shared_ptr<sf::View> worldView;
    Random<> rand;
    const int seed;
    Player player;
    ChunkManager chunkManager;

    static int generateSeed();
};



#include "World.h"


#include <iostream>

World::World(std::shared_ptr<sf::View> worldView) :
        worldView(std::move(worldView)),
        seed(generateSeed()),
        player(std::make_shared<Player>(worldConstants::INITIAL_PLAYER_POS)),
        chunkManager(seed, player, worldConstants::INITIAL_PLAYER_POS) {
}


void World::renderBy(sf::RenderTarget &renderer) {
    chunkManager.renderChunks(renderer);
}

void World::handleInput(sf::RenderWindow &window) {
    player->handleInput(window);
}

void World::update(float dt) {
    worldView->setCenter(player->getPosition());
    chunkManager.update(dt);
}

int World::generateSeed() {
    Random<> rand;
    return rand.getIntInRange(0, INT16_MAX);
}



	
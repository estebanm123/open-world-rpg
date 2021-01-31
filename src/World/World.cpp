#include "World.h"


#include <iostream>

World::World(std::shared_ptr<sf::View> worldView) :
        worldView(std::move(worldView)),
        seed(generateSeed()),
        player(worldConstants::INITIAL_PLAYER_POS),
        chunkManager(seed, &player, worldConstants::INITIAL_PLAYER_POS) {
    // testing various objects
}


void World::renderBy(sf::RenderTarget &renderer) {
    chunkManager.renderChunks(renderer);
//    for (const auto &weapon: projWeapons) {
//        // debug why weapon is not showing -> then why
//        if (weapon->isDropped()) {
//            weapon->renderBy(renderer);
//        }
//    }
    player.renderBy(renderer);
}

void World::handleInput(sf::RenderWindow &window) {
    player.handleInput(window);
}

void World::update(float dt) {
    worldView->setCenter(player.getPosition());
    chunkManager.update(dt);
}


//void World::updateWeapons(float dt) {
//    for (const auto &projWeapon : projWeapons) {
//        if (projWeapon->isDropped()) {
//            projWeapon->update(dt);
//        } else if (!projWeapon->isProjGenerationLocked()) {
//            projectiles.push_back(projWeapon->generateProjectile(player.getLookDirection(), player.getPosition()));
//        }
//    }
//}

//void World::updateProjectiles(float dt) {
//    for (auto it = projectiles.begin(); it != projectiles.end();) {
//        if ((*it)->getCurDistTravelled() >= Projectile::DESPAWN_DIST) {
//            it = projectiles.erase(it);
//        } else {
//            (*it)->update(dt);
//            ++it;
//        }
//    }
//}

int World::generateSeed() {
    Random<> rand;
    return rand.getIntInRange(0, INT16_MAX);
}



	
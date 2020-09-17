#include "World.h"


#include <iostream>

#include "../Util/CollisionChecker.h"
#include "../Util/Constants.h"
#include "Weapons/Revolver.h"

World::World(std::shared_ptr<sf::View> worldView) :
	worldView(std::move(worldView)),
	seed(generateSeed()),
	player(worldConstants::INITIAL_PLAYER_POS),
	chunkManager(seed, worldConstants::INITIAL_PLAYER_POS)
{
	curChunk = chunkManager.getChunk(constants::CENTER);
	// testing various objects
	//
	//projWeapons.push_back(std::make_shared<Revolver>(300));
	//projWeapons[0]->setPosition(450, 450);
	//sf::Vector2f pos1 = { 600,500 };
	//sf::Vector2f pos2 = { 500,550 };
	//sf::Vector2f pos3 = { 550,600 };
	//sf::Vector2f pos4 = { 500,500 };
	//sf::Vector2f pos5 = { 400,500 };
	//sf::Vector2f pos6 = { 550,550 };
	//enemies.push_back(std::make_unique<Frog>(pos1, generateRandomFloat()));
	//enemies.push_back(std::make_unique<Frog>(pos2, generateRandomFloat()));
	//enemies.push_back(std::make_unique<Frog>(pos3, generateRandomFloat()));
	//enemies.push_back(std::make_unique<Frog>(pos4, generateRandomFloat()));
	//enemies.push_back(std::make_unique<Frog>(pos5, generateRandomFloat()));
	//enemies.push_back(std::make_unique<Frog>(pos6, generateRandomFloat()));

}


void World::renderBy(sf::RenderTarget& renderer) const
{
	chunkManager.renderChunks(renderer);
	//curChunk->renderBy(renderer); // also perform rendering on other chunks - do it through chunk manager
	for (const auto& weapon: projWeapons)
	{
		// debug why weapon is not showing -> then why 
		if (weapon->isDropped()) {
			weapon->renderBy(renderer);
		}
	}

	for (const auto& projectile : projectiles)
	{
		projectile->renderBy(renderer);
	}
	for (const auto& enemy : enemies)
	{
		enemy->renderBy(renderer);
	}

	player.renderBy(renderer);

}

void World::handleInput(sf::RenderWindow& window)
{
	player.handleInput(window);
}

void World::update(float dt)
{
	player.update(dt);
	worldView->setCenter(player.getPosition());
	handleChunkChange();
	chunkManager.update(dt);
	updateEnemies(dt);
	updateWeapons(dt);
	updateProjectiles(dt);
	handleCollisions();
}

// refactor to own class?
void World::handleChunkChange()
{
	if (chunkGenerationTimer.getElapsedTime() < sf::seconds(CHUNK_GENERATION_TIMER)) return;

	chunkGenerationTimer.restart();
	auto playerPos = player.getPosition();
	bool left = playerPos.x < curChunk->getCenter().x - worldConstants::CHUNK_SIZE.x / 2.f;
	bool top = playerPos.y < curChunk->getCenter().y - worldConstants::CHUNK_SIZE.y / 2.f;
	bool right = playerPos.x > curChunk->getCenter().x + worldConstants::CHUNK_SIZE.x / 2.f;
	bool bottom = playerPos.y > curChunk->getCenter().y + worldConstants::CHUNK_SIZE.y / 2.f;
//	std::cout << curChunk->getCenter().x << ", " << curChunk->getCenter().y << std::endl;
//	std::cout << "top " << top << " bot " << bottom << " left " << left << " right " << right << std::endl;
	if (top && left)
	{
		curChunk = chunkManager.getChunk(constants::NORTH_WEST);
	}
	else if (top && right)
	{
		curChunk = chunkManager.getChunk(constants::NORTH_EAST);
	}
	else if (top)
	{
		curChunk = chunkManager.getChunk(constants::NORTH);
	}
	else if (bottom && left)
	{
		curChunk = chunkManager.getChunk(constants::SOUTH_WEST);
	}
	else if (bottom && right)
	{
		curChunk = chunkManager.getChunk(constants::SOUTH_EAST);
	}
	else if (bottom)
	{
		curChunk = chunkManager.getChunk(constants::SOUTH);
	}
	else if (right)
	{
		curChunk = chunkManager.getChunk(constants::EAST);
	}
	else if (left)
	{
		curChunk = chunkManager.getChunk(constants::WEST);
	}
	
}


void World::updateEnemies(float dt)
{
	for (const auto& enemy : enemies)
	{
		enemy->update(dt);
	}
}

void World::updateWeapons(float dt)
{
	for (const auto& projWeapon : projWeapons)
	{
		if (projWeapon->isDropped())
		{
			projWeapon->update(dt);
		}
		else if (!projWeapon->isProjGenerationLocked())
		{
			projectiles.push_back(projWeapon->generateProjectile(player.getLookDirection(), player.getPosition()));
		}
	}
}

void World::updateProjectiles(float dt)
{
	for (auto it = projectiles.begin(); it != projectiles.end();)
	{
		if ((*it)->getCurDistTravelled() >= Projectile::DESPAWN_DIST)
		{
			it = projectiles.erase(it);	
		}
		else
		{
			(*it)->update(dt);
			++it;
		}
	}
}



void World::handleCollisions()
{	
	handlePlayerDroppedWeaponCollisions();
	handleProjectileCollisions();
	handlePlayerEnemyCollisions();
}

void World::handlePlayerDroppedWeaponCollisions()
{
	for (const auto& projWeapon : projWeapons)
	{
		if (player.isPickingUp() && projWeapon->isDropped() && CollisionChecker::intersect(player.getPickUpLimit(), projWeapon->getBounds()))
		{
			player.setWeapon(projWeapon);
		}
	}
}

void World::handleProjectileCollisions()
{
	
	for (auto it = projectiles.begin(); it != projectiles.end();)
	{
		auto deleted = false;
		for (const auto& enemy : enemies)
		{
			if (CollisionChecker::intersect(enemy->getHitBox(), (*it)->getSprite()))
			{
				enemy->die();
				it = projectiles.erase(it);
				notifyObservers(Observer::ENEMY_KILLED);
				deleted = true;
				break;
			}
		}
		if (!deleted) ++it;
	}
}

void World::handlePlayerEnemyCollisions()
{
	for (const auto& enemy : enemies)
	{
		/*if (CollisionChecker::intersect(enemy->getHitBox(), player.getHitBox()))
		{
			player.die();
		}*/
	}
}

int World::generateSeed()
{
	Random<> rand;
	return rand.getIntInRange(0, INT16_MAX);
}



	
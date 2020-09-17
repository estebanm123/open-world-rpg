#pragma once
#include <SFML/Graphics/View.hpp>



#include "../Util/Observer Pattern/Subject.h"
#include "../Util/Random.h"
#include "Characters/Enemies/Enemy.h"
#include "World Generation/Chunk.h"
#include "World Generation/ChunkManager.h"
#include "World Generation/TileMap.h"
#include "Player/Player.h"
#include "Projectiles/Projectile.h"
#include "Weapons/ProjectileWeapon.h"
#include "World Generation/ChunkManager.h"

class World : Subject
{
public:
	explicit World(std::shared_ptr<sf::View> worldView);
	void renderBy(sf::RenderTarget& renderer) const;
	void handleInput(sf::RenderWindow& window);
	void update(float dt);
private:
	std::vector<std::shared_ptr<ProjectileWeapon>> projWeapons; // includes weapon held by player/ enemies
	std::vector<std::unique_ptr<Projectile>> projectiles;
	std::vector <std::unique_ptr<Enemy>> enemies;
	std::shared_ptr<sf::View> worldView;
	Random<> rand;
	const int seed;
	Player player;
	std::shared_ptr<Chunk> curChunk;
	ChunkManager chunkManager;
	sf::Clock chunkGenerationTimer;
	
	static constexpr auto CHUNK_GENERATION_TIMER = 1;

	void handleChunkChange();
	void updateEnemies(float dt);
	void updateWeapons(float dt);
	void updateProjectiles(float dt);
	
	void handleCollisions();
	void handlePlayerDroppedWeaponCollisions();
	void handleProjectileCollisions();
	void handlePlayerEnemyCollisions();
	static int generateSeed();
};



#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Util/Design patterns/Observer/Observable.h"
#include "../Util/Random/Random.h"
#include "Entities/Collidables/Hitbox/Hitbox.h"
#include "Entities/Collidables/Organisms/Humanoid/Player/Player.h"
#include "World Generation/Chunks/ChunkManager.h"

class World : Observable {
public:
	explicit World(std::shared_ptr<sf::View> worldView);

	void renderBy(sf::RenderTarget &renderer);

	void handleInput(sf::RenderWindow &window);

	void update(float dt);

private:
	std::shared_ptr<sf::View> worldView;
	const int seed;
	std::shared_ptr<Player> player;
	ChunkManager chunkManager;

	static int generateSeed();
};

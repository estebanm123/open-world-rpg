#include "Game.h"

#include "States/StatePlaying.h"
#include "Util/Random/GlobalRand.h"
#include "Util/Sprite Generation/SpriteGeneratorManager.h"
#include "World/World Generation/Environments/EnvTypes.h"

sf::RenderWindow Game::window{{1280, 720}, "Test"};

Game::Game() {
	int arbitraryPlaceholderSeed = 10;
	GlobalRand::initGlobalRand(arbitraryPlaceholderSeed);
	SpriteGeneratorManager::generateSprites();
	window.setPosition({window.getPosition().x, 0});
	window.setFramerateLimit(1000);
	EnvTypes::initialize();
	pushState<StatePlaying>(*this);
}

void Game::run() {
	constexpr unsigned TPS = 30;  //ticks per seconds
	const auto timePerUpdate = sf::seconds(1.0f / float(TPS));
	unsigned ticks = 0;

	sf::Clock timer;
	auto lastTime = sf::Time::Zero;
	auto lag = sf::Time::Zero;

	while (window.isOpen() && !states.empty()) {
		auto &state = getCurrentState();

		auto const time = timer.getElapsedTime();
		auto const elapsed = time - lastTime;
		lastTime = time;
		lag += elapsed;

		//Real time update
		state.handleInput();
		state.update(elapsed);

		//Fixed time update
		while (lag >= timePerUpdate) {
			ticks++;
			lag -= timePerUpdate;
			state.fixedUpdate(elapsed);
		}

		window.clear();
		state.render(window);
		window.display();


		//Handle window events
		handleEvent();
		tryPop();
	}
}

//Tries to pop the current game state
void Game::tryPop() {
	if (shouldPop) {
		shouldPop = false;
		if (shouldExit) {
			states.clear();
			return;
		}
		if (shouldChangeState) {
			shouldChangeState = false;
			states.pop_back();
			pushState(std::move(change));
			return;
		}

		states.pop_back();
	}
}

//Handles window events, called every frame
void Game::handleEvent() {
	sf::Event e{};

	while (window.pollEvent(e)) {
		getCurrentState().handleEvent(e);
		switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
		}
	}
}

//Returns a reference to the current game state
StateBase &Game::getCurrentState() { return *states.back(); }

void Game::pushState(std::unique_ptr<StateBase> state) { states.push_back(std::move(state)); }

//Flags a boolean for the game to pop state
void Game::popState() { shouldPop = true; }

void Game::exitGame() {
	shouldPop = true;
	shouldExit = true;
}

sf::RenderWindow &Game::getWindow() { return window; }

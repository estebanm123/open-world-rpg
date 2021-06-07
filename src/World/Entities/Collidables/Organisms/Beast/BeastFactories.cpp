#include "BeastFactories.h"

#include <memory>
#include <vector>

#include "BeastInitializer.h"
#include "BeastInitializers.h"

typedef std::vector<std::unique_ptr<InitializerMetadata<Beast, BeastInitializer::Position>>>
	InitializerMetadataCollection;

InitializerMetadataCollection constructDirtBeastInitializers() {
	auto beasts = InitializerMetadataCollection{};
	beasts.push_back(std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<CatInitializer>(), 9));

	beasts.push_back(
		std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<SnakeInitializer>(), 3));
	beasts.push_back(
		std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<BeetleInitializer>(), 10));
	beasts.push_back(
		std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<Beetle2Initializer>(), 6));
	return beasts;
}

DirtBeastFactory::DirtBeastFactory() : PositionBasedInitializerPool<Beast>(constructDirtBeastInitializers()) {}

InitializerMetadataCollection constructSandBeastInitializers() {
	auto beasts = InitializerMetadataCollection{};
	beasts.push_back(
		std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<CatInitializer>(), 10));

	beasts.push_back(
		std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<SnakeInitializer>(), 25));
	beasts.push_back(
		std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<BeetleInitializer>(), 15));
	beasts.push_back(
		std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<Beetle2Initializer>(), 10));
	return beasts;
}

SandBeastFactory::SandBeastFactory()
	: PositionBasedInitializerPool<Beast>(constructSandBeastInitializers(), 950, 1000) {}

WaterBeastFactory::WaterBeastFactory() : PositionBasedInitializerPool<Beast>({}) {}

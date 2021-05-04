#include <vector>
#include <memory>
#include "BeastFactories.h"
#include "BeastInitializer.h"
#include "BeastInitializers.h"

typedef std::vector<std::unique_ptr<InitializerMetadata<Beast, BeastInitializer::Position>>> InitializerMetadataCollection;

InitializerMetadataCollection constructDirtBeastInitializers() {
    auto beasts = InitializerMetadataCollection{};
    beasts.push_back(
            std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<CatInitializer>(), 10));

    beasts.push_back(
            std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<SnakeInitializer>(), 1));
    return beasts;
}

DirtBeastFactory::DirtBeastFactory() : PositionBasedInitializerPool<Beast>(constructDirtBeastInitializers()) {}

InitializerMetadataCollection constructSandBeastInitializers() {
    auto beasts = InitializerMetadataCollection{};
    beasts.push_back(
            std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<CatInitializer>(), 10));

    beasts.push_back(
            std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<SnakeInitializer>(), 25));
    return beasts;
}

SandBeastFactory::SandBeastFactory() : PositionBasedInitializerPool<Beast>(constructSandBeastInitializers()) {}

WaterBeastFactory::WaterBeastFactory() : PositionBasedInitializerPool<Beast>({}) {}


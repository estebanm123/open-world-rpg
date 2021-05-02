#include <vector>
#include <memory>
#include "BeastFactories.h"
#include "Beast.h"
#include "BeastInitializer.h"
#include "BeastInitializers.h"

typedef std::vector<std::unique_ptr<InitializerMetadata<Beast, BeastInitializer::Position>>> InitializerMetadataCollection;

InitializerMetadataCollection constructDirtBeastInitializers() {
    auto beasts = InitializerMetadataCollection{};
    beasts.push_back(std::make_unique<InitializerMetadata<Beast, sf::Vector2f>>(std::make_unique<CatInitializer>(), 100));
    return beasts;
}

DirtBeastFactory::DirtBeastFactory() : PositionBasedInitializerPool<Beast>(constructDirtBeastInitializers()) {}

SandBeastFactory::SandBeastFactory() : PositionBasedInitializerPool<Beast>({}) {}

WaterBeastFactory::WaterBeastFactory() : PositionBasedInitializerPool<Beast>({}) {}


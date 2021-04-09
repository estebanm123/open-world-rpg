

#include "PropFactories.h"
#include "PropInitializers.h"

// TODO: refactor to an initialize function
typedef std::vector<std::unique_ptr<InitializerMetadata<Prop, PropInitializer::Position>>> InitializerMetadataCollection;

InitializerMetadataCollection initializeSandDecorProps() {
    auto props = InitializerMetadataCollection{};
    props.push_back(std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(
            std::make_unique<CactusInitializer>(), 150));
    props.push_back(std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(
            std::make_unique<RockInitializer>(), 50));
    return props;
}

InitializerMetadataCollection initializeSandMainProps() {
    auto props = InitializerMetadataCollection{};
    props.push_back(std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(
            std::make_unique<RockCoverInitializer>(),
            100));
    return props;
}


SandPropFactory::SandPropFactory() : PropFactory(
        initializeSandDecorProps(),
        initializeSandMainProps()) {}

InitializerMetadataCollection initializeDirtDecorProps() {
    auto props = InitializerMetadataCollection{};
    props.push_back(
            std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<RockInitializer>(), 50));
    props.push_back(
            std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<BushInitializer>(), 30));
    props.push_back(
            std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<MushroomInitializer>(), 10));
    props.push_back(
            std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<SmallBushInitializer>(), 30));
    return props;
}

InitializerMetadataCollection initializeDirtMainProps() {
    auto props = InitializerMetadataCollection{};
    props.push_back(
            std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<RockCoverInitializer>(), 50));
    props.push_back(
            std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<GrassCoverInitializer>(), 60));
    return props;
}

DirtPropFactory::DirtPropFactory() : PropFactory(
        initializeDirtDecorProps(),
        initializeDirtMainProps()) {}

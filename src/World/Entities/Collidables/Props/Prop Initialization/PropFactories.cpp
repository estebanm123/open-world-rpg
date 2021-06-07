

#include "PropFactories.h"

#include "PropInitializers.h"

typedef std::vector<std::unique_ptr<InitializerMetadata<Prop, PropInitializer::Position>>>
	InitializerMetadataCollection;

InitializerMetadataCollection initializeSandMainProps() {
	auto props = InitializerMetadataCollection{};
	props.push_back(
		std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<CactusInitializer>(), 150));
	props.push_back(std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<RockInitializer>(), 50));
	return props;
}

InitializerMetadataCollection initializeSandDecorProps() {
	auto props = InitializerMetadataCollection{};
	props.push_back(
		std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<RockCoverInitializer>(), 100));
	props.push_back(
		std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<DesertGrassInitializer>(), 120));
	return props;
}

SandPropFactory::SandPropFactory() : PropFactory(initializeSandMainProps(), initializeSandDecorProps(), 70, 50) {}

InitializerMetadataCollection initializeDirtMainProps() {
	auto props = InitializerMetadataCollection{};
	props.push_back(std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<RockInitializer>(), 50));
	props.push_back(std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<BushInitializer>(), 30));
	props.push_back(
		std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<MushroomInitializer>(), 40));
	props.push_back(
		std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<SmallBushInitializer>(), 15));
	return props;
}

InitializerMetadataCollection initializeDirtDecorProps() {
	auto props = InitializerMetadataCollection{};
	props.push_back(
		std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<RockCoverInitializer>(), 50));
	props.push_back(
		std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<GrassCoverInitializer>(), 100));
	return props;
}

InitializerMetadataCollection initializeWaterDecorProps() {
	auto props = InitializerMetadataCollection{};
	props.push_back(
		std::make_unique<InitializerMetadata<Prop, sf::Vector2f>>(std::make_unique<WaterGrassInitializer>(), 60));
	return props;
}

InitializerMetadataCollection initializeWaterMainProps() {
	auto props = InitializerMetadataCollection{};
	return props;
}

WaterPropFactory::WaterPropFactory() : PropFactory(initializeWaterMainProps(), initializeWaterDecorProps(), 50, 50) {}

DirtPropFactory::DirtPropFactory() : PropFactory(initializeDirtMainProps(), initializeDirtDecorProps(), 70, 20) {}

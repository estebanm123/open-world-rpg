

#include "PropFactory.h"

std::unique_ptr<Prop> PropFactory::generateDecorProp(const PropFactory::Position &pos) {
	return decorProps.initialize(pos);
}

std::unique_ptr<Prop> PropFactory::generateMainProp(const PropFactory::Position &pos) {
	return mainProps.initialize(pos);
}

constexpr static float MAX_PROP_LIMIT = 100;

PropFactory::PropFactory(
	std::vector<std::unique_ptr<InitializerMetadata<Prop, PropInitializer::Position>>> mainPropInitializers,
	std::vector<std::unique_ptr<InitializerMetadata<Prop, PropInitializer::Position>>> decorPropInitializers,
	float mainPropScore,
	float decorPropScore)
	: decorProps(std::move(decorPropInitializers), decorPropScore, MAX_PROP_LIMIT),
	  mainProps(std::move(mainPropInitializers), mainPropScore, MAX_PROP_LIMIT) {}

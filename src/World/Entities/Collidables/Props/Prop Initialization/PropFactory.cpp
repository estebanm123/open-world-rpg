

#include "PropFactory.h"

std::unique_ptr<Prop> PropFactory::generateDecorProp(const PropFactory::Position &pos) {
    return decorProps.initialize(pos);
}

std::unique_ptr<Prop> PropFactory::generateMainProp(const PropFactory::Position &pos) {
    return mainProps.initialize(pos);
}

PropFactory::PropFactory(std::vector<std::unique_ptr<InitializerMetadata<Prop, PropInitializer::Position>>> decorPropInitializers,
                         std::vector<std::unique_ptr<InitializerMetadata<Prop, PropInitializer::Position>>> mainPropInitializers)
        : decorProps(std::move(decorPropInitializers)), mainProps(std::move(mainPropInitializers)) {}

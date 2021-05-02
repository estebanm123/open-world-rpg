#pragma once


#include "../../../../../Util/Initializer/PositionBasedInitializerPool.h"
#include "../Prop.h"
#include "PropInitializer.h"

class PropFactory {
public:

    typedef PropInitializer::Position Position;

    explicit PropFactory(std::vector<std::unique_ptr<InitializerMetadata<Prop, Position>>> mainProps,
                         std::vector<std::unique_ptr<InitializerMetadata<Prop, Position>>> decorProps,
                         float mainPropScore, float decorPropScore);

    std::unique_ptr<Prop> generateDecorProp(const Position &pos);

    std::unique_ptr<Prop> generateMainProp(const Position &pos);

private:
    PositionBasedInitializerPool<Prop> decorProps;
    PositionBasedInitializerPool<Prop> mainProps;
};
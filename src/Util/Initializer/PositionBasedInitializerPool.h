#pragma once


#include "ScoredInitializerPool.h"
#include "../Random/Hash.h"

template<class T>
class PositionBasedInitializerPool : public ScoredInitializerPool<T, sf::Vector2f> {
public:
    typedef sf::Vector2f Position;

    PositionBasedInitializerPool(std::vector<std::unique_ptr<InitializerMetadata<T, Position>>> initializers)
            : ScoredInitializerPool<T, Position>(
            std::move(initializers)) {}

    std::unique_ptr<T> initialize(Position pos) {
        return ScoredInitializerPool<T, Position>::initializeFrom(pos);
    }

protected:
    float computeScoreFrom(Position arg) override {
        return hash2ValuesModSize(arg.x, arg.y, this->initializers.size()); // safe cast (score is small)
    };
};





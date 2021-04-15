#pragma once


#include "ScoredInitializerPool.h"
#include "../Random/Hash.h"

template<class T>
class PositionBasedInitializerPool : public ScoredInitializerPool<T, sf::Vector2f> {
public:
    typedef sf::Vector2f Position;

    PositionBasedInitializerPool(std::vector<std::unique_ptr<InitializerMetadata<T, Position>>> initializers,
                                 int initializationThreshold = 400, int maxInitializationLim = 500)
            : ScoredInitializerPool<T, Position>(
            std::move(initializers)), initializationThreshold(initializationThreshold),
              maxInitializationLim(maxInitializationLim) {}

    std::unique_ptr<T> initialize(Position pos) {
        return ScoredInitializerPool<T, Position>::initializeFrom(pos);
    }

protected:
    float computeScoreFrom(Position arg) override {
        auto size = this->initializers.size();
        auto hashVal = hash2ValuesModSize(arg.x, arg.y,
                                          static_cast<int>(ScoredInitializerPool<T, sf::Vector2f>::MAX_SCORE)); // safe cast (score is small)
        return hashVal;
    };

    virtual bool shouldInitialize(Position arg) override {
        auto hashVal = hash2ValuesModSize(arg.y, arg.x, maxInitializationLim, RAND_MIXER_2);
        return hashVal > initializationThreshold;
    }

private:
    int initializationThreshold;
    int maxInitializationLim;

};





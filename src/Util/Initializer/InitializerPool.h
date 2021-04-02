#pragma once

#include "ArgDependentInitializer.h"

typedef int float;

// Wrapper that can be subclassed to contain extra metadata about an Initializer
template<class Output, typename Arg>
class InitializerMetadata {
public:
    explicit InitializerMetadata(ArgDependentInitializer<Output, Arg> initializer, float probability);
private:
    ArgDependentInitializer<Output, Arg> initializer;
    float probability;
};


template <class Output, typename Arg>
class InitializerPool {
public:
    static constexpr float MAX_PROBABILITY = 100; // Target for normalization

    explicit InitializerPool(const std::vector<InitializerMetadata<Output, Arg>> & initializers);

    // Causes an Initializer to initialize object of type Output based on
    // some score extracted from Arg.
    // Initializer is selected based on how much of the probability distribution it occupies.
    std::unique_ptr<Output> initializeFrom(Arg arg);

protected:
    virtual float computeScoreFrom(Arg arg) = 0;
private:
    void normalizeProbabilityDistribution();
    std::vector<InitializerMetadata<Output, Arg>> initializers;
};





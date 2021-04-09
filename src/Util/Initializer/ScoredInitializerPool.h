#pragma once

#include "ArgDependentInitializer.h"

// Wrapper that can be subclassed to contain extra metadata about an Initializer
template<class Output, typename Arg>
struct InitializerMetadata {
    InitializerMetadata(std::unique_ptr<ArgDependentInitializer<Output, Arg>> initializer, float score)
            : initializer(std::move(initializer)), score(score) {}

    std::unique_ptr<ArgDependentInitializer<Output, Arg>> initializer;
    float score;
};

template<class Output, typename Arg>
class ScoredInitializerPool {
public:
    typedef std::vector<std::unique_ptr<InitializerMetadata<Output, Arg>>> InitializerMetadataCollection;

    static constexpr float MAX_SCORE = 100;

    explicit ScoredInitializerPool(
            std::vector<std::unique_ptr<InitializerMetadata<Output, Arg>>> initializers) : initializers(
            std::move(initializers)) {
        normalizeScoreDistribution();
    }

    // Causes an Initializer to initialize object of type Output based on
    // some score extracted from Arg.
    // Initializer is selected based on how much of the score distribution it occupies.
    std::unique_ptr<Output> initializeFrom(Arg arg) {
        float score = computeScoreFrom(std::move(arg));
        for (auto &metadata : initializers) {
            if (metadata->score <= score) {
                auto x = metadata->initializer->initialize(arg);
                return x;
            }
        }
    }

protected:
    virtual float computeScoreFrom(Arg arg) = 0;

    InitializerMetadataCollection initializers;

private:
    struct InitializerMetadataCompare {
        bool operator()(InitializerMetadata<Output, Arg> a, InitializerMetadata<Output, Arg> b) const {
            return a.score < b.score;
        }
    };

    void normalizeScoreDistribution() {
//        std::sort(initializers.begin(), initializers.end(), InitializerMetadataCompare<Output, Arg>{}); // todo: uncomment

        float sum = 0;
        for (auto &metadata : initializers) {
            sum += metadata->score;
        }

        float normalizingScalar = MAX_SCORE / sum;
        float sumToDistribute = MAX_SCORE;
        for (auto &metadata : initializers) {
            auto normalizedProbability = metadata->score * normalizingScalar;
            sumToDistribute -= normalizedProbability;
            metadata->score = sumToDistribute; // should probably refactor assignment to another variable for clarity [eg. score bound]
        }

        // For safety, set the last score bound to 0
        initializers[initializers.size() - 1]->score = 0;
    }

};





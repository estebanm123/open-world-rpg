

#include "InitializerPool.h"

template<class Output, typename Arg>
std::unique_ptr<Output> InitializerPool<Output, Arg>::initializeFrom(Arg arg) {
    float score = computeScoreFrom(std::move(arg));
    for (auto &metadata : initializers) {
        if (metadata.probability <= score) {
            return metadata.initializer.initialize(arg);
        }
    }
}

template<class Output, typename Arg>
struct InitializerMetadataCompare {
    bool operator()(InitializerMetadata<Output, Arg> a, InitializerMetadata<Output, Arg> b) const {
        return a.probability < b.probability;
    }
};

template<class Output, typename Arg>
void InitializerPool<Output, Arg>::normalizeProbabilityDistribution() {
    std::sort(initializers.begin(), initializers.end(), InitializerMetadataCompare<Output, Arg>{});

    float sum = 0;
    for (auto &metadata : initializers) {
        sum += metadata.probability;
    }

    float normalizingScalar = MAX_PROBABILITY / sum;
    for (auto &metadata : initializers) {
        metadata.probability *= normalizingScalar;
    }
}

template<class Output, typename Arg>
InitializerPool<Output, Arg>::InitializerPool(
        const std::vector<InitializerMetadata<Output, Arg>> &initializers) : initializers(initializers) {
    normalizeProbabilityDistribution();
}

template<class Output, typename Arg>
InitializerMetadata<Output, Arg>::InitializerMetadata(ArgDependentInitializer<Output, Arg> initializer,
                                                      float probability)
        : initializer(std::move(initializer)), probability(probability) {}

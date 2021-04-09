

#include "ScoredInitializerPool.h"

//template<class Output, typename Arg>
//std::unique_ptr<Output> ScoredInitializerPool<Output, Arg>::initializeFrom(Arg arg) {
//    float score = computeScoreFrom(std::move(arg));
//    for (auto &metadata : initializers) {
//        if (metadata->score <= score) {
//            return metadata.initializer->initialize(arg);
//        }
//    }
//}
//
//template<class Output, typename Arg>
//struct InitializerMetadataCompare {
//    bool operator()(InitializerMetadata<Output, Arg> a, InitializerMetadata<Output, Arg> b) const {
//        return a.score < b.score;
//    }
//};

//template<class Output, typename Arg>
//void ScoredInitializerPool<Output, Arg>::normalizeScoreDistribution() {
//    std::sort(initializers.begin(), initializers.end(), InitializerMetadataCompare<Output, Arg>{});
//
//    float sum = 0;
//    for (auto &metadata : initializers) {
//        sum += metadata->score;
//    }
//
//    float normalizingScalar = MAX_SCORE / sum;
//    float sumToDistribute = MAX_SCORE;
//    for (auto &metadata : initializers) {
//        auto normalizedProbability = metadata->score * normalizingScalar;
//        sumToDistribute -= normalizedProbability;
//        metadata->score = sumToDistribute; // should probably refactor assignment to another variable for clarity [eg. score bound]
//    }
//
//    // For safety, set the last score bound to 0
//    initializers[initializers.size() - 1].probability = 0;
//}
//
//template<class Output, typename Arg>
//ScoredInitializerPool<Output, Arg>::ScoredInitializerPool(
//        std::vector<std::unique_ptr<InitializerMetadata<Output, Arg>>> initializers) : initializers(
//        std::move(initializers)) {
//    normalizeScoreDistribution();
//}

//
//template<class Output, typename Arg>
//InitializerMetadata<Output, Arg>::InitializerMetadata(std::unique_ptr<ArgDependentInitializer<Output, Arg>> initializer,
//                                                      float score)
//        : initializer(std::move(initializer)), score(score) {}

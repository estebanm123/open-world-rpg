

#include "PositionBasedInitializerPool.h"

//template<class T>
//PositionBasedInitializerPool<T>::PositionBasedInitializerPool(
//        std::vector<std::unique_ptr<InitializerMetadata<T, Position>>> initializers): ScoredInitializerPool<T, Position>(
//        std::move(initializers)) {}
//
//template<class T>
//std::unique_ptr<T> PositionBasedInitializerPool<T>::initialize(PositionBasedInitializerPool::Position pos) {
//    return ScoredInitializerPool<T, Position>::initializeFrom(pos);
//}

//template<class T>
//float PositionBasedInitializerPool<T>::computeScoreFrom(PositionBasedInitializerPool::Position arg) {
//    return hash2ValuesModSize(arg.x, arg.y,
//                              ScoredInitializerPool<T, Position>::initializers.size()); // safe cast (score is small)
//}

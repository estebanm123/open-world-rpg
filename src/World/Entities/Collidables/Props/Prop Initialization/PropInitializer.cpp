

#include "PropInitializer.h"
#include "../../../../../Util/Random/Hash.h"

#include <utility>

std::unique_ptr<Prop> PropInitializer::initialize(PositionBasedInitializer::Position pos) {
    auto index = hash2ValuesModSize(pos.y, pos.x, variants.size());
    auto selectedVariant = variants[index];
    return initializeProp(pos, selectedVariant);
}

PropInitializer::PropInitializer(std::vector<sf::IntRect> variants) : variants(std::move(variants)) {}

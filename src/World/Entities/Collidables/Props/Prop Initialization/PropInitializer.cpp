

#include "PropInitializer.h"
#include "../../../../../Util/Random/Hash.h"
#include <utility>
#include "../Prop.h"


std::unique_ptr<Prop> PropInitializer::initialize(Position pos) {
    auto index = hash2ValuesModSize(pos.y, pos.x, variants.size());
    auto selectedVariant = variants[index];
    return initializeProp(pos, selectedVariant, index);
}

PropInitializer::PropInitializer(std::vector<sf::IntRect> variants) : variants(std::move(variants)) {}

int PropInitializer::computeAnimStartFrame(int variantIndex) {
    if (variantIndex == 0) {
        return variants[0].left;
    } else {
        return variants[variantIndex - 1].left;
    }
}

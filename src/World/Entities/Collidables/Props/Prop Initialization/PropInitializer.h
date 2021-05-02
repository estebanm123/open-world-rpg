#pragma once


#include <SFML/Graphics/Rect.hpp>
#include "../../../../../Util/Initializer/ArgDependentInitializer.h"

class Prop;

// Wraps initialization process of a Prop, so it can be passed around/treated like an object
class PropInitializer : public ArgDependentInitializer<Prop, sf::Vector2f> {
public:
    typedef sf::Vector2f Position;

    explicit PropInitializer(std::vector<sf::IntRect> variants);

    std::unique_ptr<Prop> initialize(Position pos) override;

    virtual std::unique_ptr<Prop>
    initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) = 0;

private:
    std::vector<sf::IntRect> variants;
};





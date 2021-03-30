#pragma once


#include <SFML/Graphics/Rect.hpp>
#include "../../../../../Util/PositionBasedInitializer.h"

class Prop;

// Wraps initialization process of a Prop, so it can be passed around/treated like an object
class PropInitializer : public PositionBasedInitializer<Prop> {
public:
    explicit PropInitializer(std::vector<sf::IntRect> variants);

    std::unique_ptr<Prop> initialize(PositionBasedInitializer::Position pos) override;

    virtual std::unique_ptr<Prop>
    initializeProp(PositionBasedInitializer::Position pos, sf::IntRect spriteSheetCoords) = 0;

private:
    std::vector<sf::IntRect> variants;
};





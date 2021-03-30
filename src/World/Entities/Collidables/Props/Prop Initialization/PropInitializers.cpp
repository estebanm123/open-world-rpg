

#include "PropInitializers.h"
#include "../Prop.h"
#include "../../../../../Animation/RepeatingAnim.h"

const std::string FOLIAGE = "Foliage/";
const std::string FOLIAGE_SHADOW = FOLIAGE + "Shadow/";
constexpr auto SIZE_FLEX = 5; // temp

MushroomInitializer::MushroomInitializer() : PropInitializer(std::vector<sf::IntRect>{{0, 0, 22, 20}}) {}

std::unique_ptr<Prop>
MushroomInitializer::initializeProp(PositionBasedInitializer::Position pos, sf::IntRect spriteSheetCoords) {
    return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE_SHADOW + "Mushroom", spriteSheetCoords, pos, true});
}

CactusInitializer::CactusInitializer() : PropInitializer(std::vector<sf::IntRect>{{{0, 0, 22, 20}}}) {}

std::unique_ptr<Prop>
CactusInitializer::initializeProp(PositionBasedInitializer::Position pos, sf::IntRect spriteSheetCoords) {
    return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE_SHADOW + "Cactus", spriteSheetCoords, pos, true, {0, 0},
                                                    std::make_unique<BlockingPhysics>()});
}

BushInitializer::BushInitializer() : PropInitializer(std::vector<sf::IntRect>{{0, 0, 36, 32}}) {}

std::unique_ptr<Prop>
BushInitializer::initializeProp(PositionBasedInitializer::Position pos, sf::IntRect spriteSheetCoords) {
    int delay = 200;
    int start = 0;
    int end = 2;
    Animation::Metadata data(spriteSheetCoords.width, spriteSheetCoords.height, start, end, 0, delay, {});
    return std::make_unique<Prop>(
            Prop::PropOptions{FOLIAGE_SHADOW + "ForestFoliage", spriteSheetCoords, pos, true, {SIZE_FLEX, SIZE_FLEX},
                              std::make_unique<BlockingPhysics>(),
                              std::make_unique<AnimationPlayer>(std::make_unique<RepeatingAnim>(data))});
}

GrassCoverInitializer::GrassCoverInitializer() : PropInitializer(std::vector<sf::IntRect>{
        {0,   0, 64, 64},
        {64,  0, 64, 64},
        {128, 0, 64, 64},
}) {}

std::unique_ptr<Prop>
GrassCoverInitializer::initializeProp(PositionBasedInitializer::Position pos, sf::IntRect spriteSheetCoords) {
    return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE + "GrassOverlays", spriteSheetCoords, pos});
}

RockInitializer::RockInitializer() : PropInitializer(std::vector<sf::IntRect>{{
                                                                                      {0, 0, 29, 28},
                                                                                      {29, 0, 52, 52},
                                                                                      {81, 0, 25, 29},
                                                                                      {106, 0, 29, 29}
                                                                              }}) {}

std::unique_ptr<Prop>
RockInitializer::initializeProp(PositionBasedInitializer::Position pos, sf::IntRect spriteSheetCoords) {
    return std::make_unique<Prop>(
            Prop::PropOptions{FOLIAGE_SHADOW + "Rocks", spriteSheetCoords, pos, true, {SIZE_FLEX, SIZE_FLEX},
                              std::make_unique<BlockingPhysics>()});
}



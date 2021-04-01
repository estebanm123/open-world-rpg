#pragma once

#include "PropInitializer.h"

class GrassCoverInitializer : public PropInitializer {
    GrassCoverInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

class MushroomInitializer : public PropInitializer {
    MushroomInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

class CactusInitializer : public PropInitializer {
    CactusInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

class BushInitializer : public PropInitializer {
    BushInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

class RockInitializer : public PropInitializer {
    RockInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};



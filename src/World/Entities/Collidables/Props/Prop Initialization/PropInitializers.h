#pragma once

#include "PropInitializer.h"

struct GrassCoverInitializer : public PropInitializer {
    GrassCoverInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

struct RockCoverInitializer : public PropInitializer {
    RockCoverInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

struct MushroomInitializer : public PropInitializer {
    MushroomInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

struct CactusInitializer : public PropInitializer {
    CactusInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

struct DesertGrassInitializer : public PropInitializer {
    DesertGrassInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

struct BushInitializer : public PropInitializer {
    BushInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

// todo: make a variant of bush?
struct SmallBushInitializer : public PropInitializer {
    SmallBushInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};

struct RockInitializer : public PropInitializer {
    RockInitializer();
    std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords) override;
};




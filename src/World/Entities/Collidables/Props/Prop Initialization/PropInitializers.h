#pragma once

#include "PropInitializer.h"

struct GrassCoverInitializer : public PropInitializer {
	GrassCoverInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

struct WaterGrassInitializer : public PropInitializer {
	WaterGrassInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

struct RockCoverInitializer : public PropInitializer {
	RockCoverInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

struct MushroomInitializer : public PropInitializer {
	MushroomInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

struct CactusInitializer : public PropInitializer {
	CactusInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

struct DesertGrassInitializer : public PropInitializer {
	DesertGrassInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

struct BushInitializer : public PropInitializer {
	BushInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

// todo: make a variant of bush?
struct SmallBushInitializer : public PropInitializer {
	SmallBushInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

struct RockInitializer : public PropInitializer {
	RockInitializer();
	std::unique_ptr<Prop> initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) override;
};

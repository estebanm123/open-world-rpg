

#include "PropInitializers.h"

#include "../../../../../Animation/RepeatingAnim.h"
#include "../../Collision Physics/BlockingPhysics.h"
#include "../Prop.h"

const std::string FOLIAGE = "Foliage/";
const std::string FOLIAGE_SHADOW = FOLIAGE + "Shadow/";

// TODO: rename to something more generic or extract flowers into separate initializer
MushroomInitializer::MushroomInitializer()
	: PropInitializer(std::vector<sf::IntRect>{{0, 0, 22, 20}, {22, 0, 13, 15}, {35, 0, 18, 16}}) {}

std::unique_ptr<Prop> MushroomInitializer::initializeProp(Position pos,
														  sf::IntRect spriteSheetCoords,
														  int variantIndex) {
	return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE_SHADOW + "Mushroom", spriteSheetCoords, pos, true});
}

CactusInitializer::CactusInitializer() : PropInitializer(std::vector<sf::IntRect>{{{0, 0, 22, 20}}}) {}

std::unique_ptr<Prop> CactusInitializer::initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) {
	return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE_SHADOW + "Cactus",
													spriteSheetCoords,
													pos,
													true,
													{0, 0},
													std::make_unique<BlockingPhysics>()});
}

BushInitializer::BushInitializer() : PropInitializer(std::vector<sf::IntRect>{{0, 0, 36, 28}, {36 * 3, 0, 39, 30}}) {}

std::unique_ptr<Prop> BushInitializer::initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) {
	int delay = 200;
	int start = 0;
	int end = 2;
	Animation::Metadata data(spriteSheetCoords.width,
							 spriteSheetCoords.height,
							 start,
							 end,
							 0,
							 delay,
							 {},
							 Animation::Priority::LOW,
							 25,
							 false,
							 {spriteSheetCoords.left, spriteSheetCoords.top});
	return std::make_unique<Prop>(
		Prop::PropOptions{FOLIAGE_SHADOW + "ForestFoliage",
						  spriteSheetCoords,
						  pos,
						  true,
						  {0, 0},
						  std::make_unique<BlockingPhysics>(),
						  std::make_unique<AnimationPlayer>(std::make_unique<RepeatingAnim>(data))});
}

GrassCoverInitializer::GrassCoverInitializer()
	: PropInitializer(std::vector<sf::IntRect>{{0, 0, 64, 64},
											   {64, 0, 64, 64},
											   {128, 0, 64, 64},
											   {192, 0, 64, 64},
											   {256, 0, 64, 64}}) {}

std::unique_ptr<Prop> GrassCoverInitializer::initializeProp(Position pos,
															sf::IntRect spriteSheetCoords,
															int variantIndex) {
	return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE + "GrassOverlays", spriteSheetCoords, pos});
}

RockInitializer::RockInitializer()
	: PropInitializer(std::vector<sf::IntRect>{
		  {{0, 0, 29, 28}, {29, 0, 52, 52}, {81, 0, 25, 29}, {106, 0, 29, 29}, {135, 0, 19, 18}}}) {}

std::unique_ptr<Prop> RockInitializer::initializeProp(Position pos, sf::IntRect spriteSheetCoords, int variantIndex) {
	return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE_SHADOW + "Rocks",
													spriteSheetCoords,
													pos,
													true,
													{-5, -5},
													std::make_unique<BlockingPhysics>()});
}

RockCoverInitializer::RockCoverInitializer()
	: PropInitializer(std::vector<sf::IntRect>{{
		  {0, 0, 31, 34},
		  {31, 0, 31, 34},
		  {62, 0, 31, 34},
	  }}) {}

std::unique_ptr<Prop> RockCoverInitializer::initializeProp(PropInitializer::Position pos,
														   sf::IntRect spriteSheetCoords,
														   int variantIndex) {
	return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE + "RocksOverlays", spriteSheetCoords, pos});
}

SmallBushInitializer::SmallBushInitializer() : PropInitializer(std::vector<sf::IntRect>{{{0, 0, 18, 16}}}) {}

std::unique_ptr<Prop> SmallBushInitializer::initializeProp(PropInitializer::Position pos,
														   sf::IntRect spriteSheetCoords,
														   int variantIndex) {
	Animation::Metadata
		data(spriteSheetCoords.width, spriteSheetCoords.height, 0, 2, 0, 250, {}, Animation::Priority::LOW, 50);
	return std::make_unique<Prop>(
		Prop::PropOptions{FOLIAGE_SHADOW + "SmallBush1",
						  spriteSheetCoords,
						  pos,
						  true,
						  {-2, -2},
						  std::make_unique<CollisionPhysics>(),
						  std::make_unique<AnimationPlayer>(std::make_unique<RepeatingAnim>(data))});
}

std::unique_ptr<Prop> DesertGrassInitializer::initializeProp(PropInitializer::Position pos,
															 sf::IntRect spriteSheetCoords,
															 int variantIndex) {
	return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE + "DesertGrassOverlays", spriteSheetCoords, pos});
}

DesertGrassInitializer::DesertGrassInitializer()
	: PropInitializer(std::vector<sf::IntRect>{{{0, 0, 68, 41}, {68, 0, 68, 41}, {68 * 2, 0, 68, 41}

	  }}) {}

WaterGrassInitializer::WaterGrassInitializer() : PropInitializer(std::vector<sf::IntRect>{{0, 0, 96, 76}}) {}

std::unique_ptr<Prop> WaterGrassInitializer::initializeProp(PropInitializer::Position pos,
															sf::IntRect spriteSheetCoords,
															int variantIndex) {
	return std::make_unique<Prop>(Prop::PropOptions{FOLIAGE + "SeaGrass", spriteSheetCoords, pos});
}

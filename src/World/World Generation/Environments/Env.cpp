
#include "Env.h"

#include "../../Entities/Collidables/Organisms/NPC AI/NpcAi.h"
#include "EnvNeighborInfo.h"
#include "Temporary Environments/EnvWrapper.h"

Env::Env(std::unique_ptr<Env::Config> config)
	: tempConfig(std::move(config)),
	  spriteSheet(tempConfig->spriteSheet),
	  propFactory(std::move(tempConfig->propFactory)),
	  beastFactory(std::move(tempConfig->beastFactory)){};

TileContainer *Env::selectTileContainer(const sf::Vector2f &coords) const {
	// todo: refactor to a separate class when tile fetching gets more complex
	auto tileContainerIndex = hash2ValuesModSize(coords.x, coords.y, completeTileContainers.size());
	auto tileContainer = completeTileContainers[tileContainerIndex].get();
	return tileContainer;
}

const std::string &Env::getSpriteSheetPath() const { return spriteSheet; }

TileContainer *getBorderTileContainerUtil(const Env *otherEnv,
										  const Env::BorderTileContainers &borderTileContainers,
										  const sf::Vector2f &globalCoords) {
	// todo: could there be a case where otherEnv == this?
	if (borderTileContainers.find(otherEnv) == borderTileContainers.end()) return nullptr;
	const auto &borderContainers = borderTileContainers.at(otherEnv);
	if (borderContainers.empty()) return nullptr;
	int hashVal = hash2ValuesModSize(globalCoords.x, globalCoords.y, borderContainers.size());
	return borderContainers.at(hashVal).get();
}

TileContainer *Env::getSplitTileContainer(const Env *otherEnv, const sf::Vector2f &globalCoords) const {
	// check to see what in the maps
	return getBorderTileContainerUtil(otherEnv, splitBorderTileContainers, globalCoords);
}

TileContainer *Env::getCornerTileContainer(const Env *otherEnv, const sf::Vector2f &globalCoords) const {
	return getBorderTileContainerUtil(otherEnv, cornerBorderTileContainers, globalCoords);
}

void Env::setBorderTileContainers(const BorderTileContainers &splits, const BorderTileContainers &corners) {
	splitBorderTileContainers = splits;
	cornerBorderTileContainers = corners;
}

std::unique_ptr<Prop> Env::generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const {
	if (!propFactory) return nullptr;
	if (isDecor) {
		return propFactory->generateDecorProp(propCoords);
	} else {
		return propFactory->generateMainProp(propCoords);
	}
}

bool Env::operator==(const CompleteEnv &other) const { return &other == this; }

void Env::setPropFactory(std::unique_ptr<PropFactory> inputPropFactory) { propFactory = std::move(inputPropFactory); }

Env::Config *Env::getConfig() { return tempConfig.get(); }

std::unique_ptr<Beast> Env::generateBeast(const sf::Vector2f &beastCoords) const {
	if (!beastFactory) return nullptr;
	return beastFactory->initialize(beastCoords);
}

void Env::setSpriteSheet(std::string inputSpriteSheet) { spriteSheet = std::move(inputSpriteSheet); }

void Env::setCompleteTileContainers(const TileContainer::TileContainers &tileContainers) {
	completeTileContainers = tileContainers;
}

int *Env::getId() const { return &tempConfig->id; }

const std::vector<std::unique_ptr<SurfaceEffectGenerator>> *Env::getSurfaceEffectGenerators() const {
	return &surfaceEffectGenerators;
};

Env::Config::Config(EnvId id,
					std::string spriteSheet,
					int numFullTiles,
					std::vector<EnvNeighborInfo> borderData,
					std::unique_ptr<PropFactory> propFactory,
					std::unique_ptr<BeastFactory> beastFactory,
					std::unique_ptr<Animation::BaseMetadata> animMetadata)
	: id(id),
	  spriteSheet(std::move(spriteSheet)),
	  numFullTiles(numFullTiles),
	  borderDataCollection(std::move(borderData)),
	  propFactory(std::move(propFactory)),
	  beastFactory(std::move(beastFactory)),
	  animMetadata(std::move(animMetadata)) {}

#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <unordered_map>

#include "../../../Util/Constants.h"
#include "../../../Util/NonMoveable.h"
#include "../../Entities/Collidables/Props/Prop Initialization/PropFactory.h"
#include "../Tiles/TileContainers/TileContainer.h"
#include "CompleteEnv.h"

class SingleTileContainer;

class Prop;

class EnvWrapper;

class EnvNeighborInfo;

class BeastFactory;

// A mediator for Entity and Tile generation; anything drastically influenced
// by an Env
class Env : public CompleteEnv, sf::NonCopyable, NonMoveable {
public:
	typedef std::unordered_map<const Env *, TileContainer::TileContainers> BorderTileContainers;
	typedef int EnvId;
	typedef PositionBasedInitializerPool<Beast> BeastFactory;

	struct Config {
		Config(EnvId id,
			   std::string spriteSheet,
			   int numFullTiles,
			   std::vector<EnvNeighborInfo> borderData,
			   std::unique_ptr<PropFactory> propFactory = nullptr,
			   std::unique_ptr<BeastFactory> beastFactory = nullptr,
			   std::unique_ptr<Animation::BaseMetadata> animMetadata = nullptr);

		EnvId id;
		std::string spriteSheet;
		int numFullTiles;
		std::vector<EnvNeighborInfo> borderDataCollection;
		std::unique_ptr<BeastFactory> beastFactory;
		//        int multiTileIndex = -1;
		std::unique_ptr<PropFactory> propFactory;
		std::unique_ptr<Animation::BaseMetadata> animMetadata;
	};

	explicit Env(std::unique_ptr<Config> config);

	const std::string &getSpriteSheetPath() const;

	bool operator==(const CompleteEnv &other) const;

	void setBorderTileContainers(const BorderTileContainers &splits, const BorderTileContainers &corners);

	// Could return null if there is no associated border tile container
	TileContainer *getSplitTileContainer(const Env *, const sf::Vector2f &globalCoords) const;

	TileContainer *getCornerTileContainer(const Env *, const sf::Vector2f &globalCoords) const;

	TileContainer *selectTileContainer(const sf::Vector2f &coords) const;

	std::unique_ptr<Prop> generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const override;

	void setPropFactory(std::unique_ptr<PropFactory> propFactory);

	void setSpriteSheet(std::string spriteSheet);

	void setCompleteTileContainers(const TileContainer::TileContainers &completeTileContainers);

	Config *getConfig();

	const std::vector<std::unique_ptr<SurfaceEffectGenerator>> *getSurfaceEffectGenerators() const override;

	std::unique_ptr<Beast> generateBeast(const sf::Vector2f &beastCoords) const override;

	int *getId() const override;

private:
	std::unique_ptr<Config> tempConfig;
	TileContainer::TileContainers completeTileContainers;
	BorderTileContainers splitBorderTileContainers;
	BorderTileContainers cornerBorderTileContainers;
	std::unique_ptr<PropFactory> propFactory;
	std::unique_ptr<BeastFactory> beastFactory;
	std::vector<std::unique_ptr<SurfaceEffectGenerator>> surfaceEffectGenerators;
	std::string spriteSheet;
};

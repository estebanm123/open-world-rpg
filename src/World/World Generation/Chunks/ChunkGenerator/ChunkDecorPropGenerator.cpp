#include "ChunkDecorPropGenerator.h"

#include "../../Environments/Env.h"

bool ChunkDecorPropGenerator::isEntityValid(Entity *entity,
											const TileMap &tiles,
											ChunkEnvBasedEntityGenerator::TilesSeen &tilesSeen,
											const sf::Vector2i &localCoords) {
	return entity != nullptr;
}

std::unique_ptr<Entity> ChunkDecorPropGenerator::generateEntity(const CompleteEnv *curEnv, sf::Vector2f entityCoords) {
	auto prop = curEnv->generateEnvironmentalProp(entityCoords, true);
	if (prop) {
		prop->setIsDecor(true);
	}
	return prop;
}
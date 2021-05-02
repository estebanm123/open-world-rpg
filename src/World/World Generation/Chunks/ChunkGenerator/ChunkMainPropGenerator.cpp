

#include "ChunkMainPropGenerator.h"
#include "../../Environments/Env.h"

std::unique_ptr<Entity> ChunkMainPropGenerator::generateEntity(const CompleteEnv *curEnv, sf::Vector2f entityCoords) {
    return curEnv->generateEnvironmentalProp(entityCoords, false);
}
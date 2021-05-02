

#include "ChunkBeastGenerator.h"
#include "../../../Entities/Entity.h"
#include "../../Environments/Env.h"

std::unique_ptr<Entity> ChunkBeastGenerator::generateEntity(const CompleteEnv *curEnv, sf::Vector2f entityCoords) {
    auto beast = curEnv->generateBeast(entityCoords);
    return beast;
}
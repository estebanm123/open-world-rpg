

#include "ChunkBeastGenerator.h"
#include "../../../Entities/Entity.h"
#include "../../Environments/Env.h"
#include "../../../Entities/Collidables/Organisms/NPC AI/NpcAi.h"

std::unique_ptr<Entity> ChunkBeastGenerator::generateEntity(const CompleteEnv *curEnv, sf::Vector2f entityCoords) {
    return curEnv->generateBeast(entityCoords);
}
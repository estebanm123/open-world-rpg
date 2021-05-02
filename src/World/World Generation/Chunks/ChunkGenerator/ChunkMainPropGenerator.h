#pragma once


#include "ChunkEnvBasedEntityGenerator.h"
#include "../../Environments/CompleteEnv.h"

class ChunkMainPropGenerator : public ChunkEnvBasedEntityGenerator {
protected:
    std::unique_ptr<Entity> generateEntity(const CompleteEnv *curEnv, sf::Vector2f entityCoords) override;
};





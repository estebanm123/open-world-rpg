#pragma once

#include "ChunkEnvBasedEntityGenerator.h"


class ChunkBeastGenerator :  public ChunkEnvBasedEntityGenerator {
protected:
    std::unique_ptr<Entity> generateEntity(const CompleteEnv *curEnv, sf::Vector2f entityCoords) override;
};





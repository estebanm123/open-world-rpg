#pragma once


#include "../../../Animation/Animation.h"
#include "EnvManager.h"
#include "EnvNeighborInfo.h"
#include "Env.h"
#include "../../Entities/Collidables/Props/Prop Initialization/PropFactories.h"
#include "../../Entities/Collidables/Organisms/Beast/BeastFactories.h"


namespace EnvTypes {

    using namespace worldConstants;
    using namespace animConstants;

    // Refactor to enum??
    inline constexpr Env::EnvId WATER = 1;
    inline constexpr Env::EnvId DIRT = 2;
    inline constexpr Env::EnvId SAND = 3;

    inline void initialize() {
        EnvManager::createEnv(std::make_unique<Env::Config>(
                WATER, "Tiles/Water", 1, std::vector<EnvNeighborInfo>{EnvNeighborInfo{DIRT, 0, 2}},
                std::make_unique<WaterPropFactory>(),
                std::make_unique<WaterBeastFactory>(),
                std::make_unique<Animation::BaseMetadata>(0, 2, 220)
        ));

        EnvManager::createEnv(std::make_unique<Env::Config>(
                DIRT, "Tiles/Dirt", 6,
                std::vector<EnvNeighborInfo>{EnvNeighborInfo{WATER, 1, 3}, EnvNeighborInfo{SAND, 0, 3}},
                std::make_unique<DirtPropFactory>(),
                std::make_unique<DirtBeastFactory>()
        ));

        EnvManager::createEnv(std::make_unique<Env::Config>(
                SAND, "Tiles/Sand", 4,
                std::vector<EnvNeighborInfo>{EnvNeighborInfo{DIRT, 2, 2}},
                std::make_unique<SandPropFactory>(),
                std::make_unique<SandBeastFactory>()));

        EnvManager::initializeEnvs();
    }

}




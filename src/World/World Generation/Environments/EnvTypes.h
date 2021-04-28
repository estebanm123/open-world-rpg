#pragma once


#include "../../../Animation/Animation.h"
#include "EnvManager.h"
#include "EnvNeighborInfo.h"
#include "Env.h"
#include "../../Entities/Collidables/Props/Prop Initialization/PropFactories.h"


namespace EnvTypes {

    using namespace worldConstants;
    using namespace animConstants;

    // Refactor to enum??
    inline constexpr Env::EnvId WATER = 1;
    inline constexpr Env::EnvId DIRT = 2;
    inline constexpr Env::EnvId SAND = 3;

    inline void initialize() {
        EnvManager::createEnv(std::make_unique<Env::Config>(
                WATER, "Tiles/Water", 1, std::vector<EnvNeighborInfo>{EnvNeighborInfo{DIRT, 0, 1}},
                std::make_unique<WaterPropFactory>(),
                std::make_unique<Animation::BaseMetadata>(0, 2, 220)
        ));

        EnvManager::createEnv(std::make_unique<Env::Config>(
                DIRT, "Tiles/Dirt", 6,
                std::vector<EnvNeighborInfo>{EnvNeighborInfo{WATER, 1, 1}, EnvNeighborInfo{SAND, 0, 1}},
                std::make_unique<DirtPropFactory>()
        ));

        EnvManager::createEnv(std::make_unique<Env::Config>(
                SAND, "Tiles/Sand", 3,
                std::vector<EnvNeighborInfo>{EnvNeighborInfo{DIRT, 2, 1}}, std::make_unique<SandPropFactory>()
        ));

        EnvManager::initializeEnvs();
    }

}




#pragma once

#include <unordered_map>
#include "Env.h"

class EnvManager {
public:
    static void createEnv(std::unique_ptr<Env::Config> config);

    static void initializeEnvs();

    static const Env * getEnv(Env::EnvId);
private:
    static std::unordered_map<Env::EnvId, std::unique_ptr<Env>> envs;

    static void initializeCompleteTileContainers(Env * env);

    static void initializeBorderTileContainers(Env * env);
};





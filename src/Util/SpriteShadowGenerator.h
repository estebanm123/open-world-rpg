#pragma once
#include <unordered_set>



struct SpriteShadowGenerator {
    const static std::string SHADOW_SUFFIX;
    const static std::unordered_set<std::string> DIRECTORIES;

    // NOTE: Clears texture manager cache
    static void generateMissingShadowSprites();
};





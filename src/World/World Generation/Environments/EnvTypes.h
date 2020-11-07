#pragma once

#include <memory>
#include "Env.h"

namespace EnvTypes {
    const inline std::string TILE_SHEET_PATH = "Levels/tileMap";

    // typedef for makeshared<TileContainer>

    Env *test = new Env(TILE_SHEET_PATH,
                        std::vector<std::shared_ptr<TileContainer>>{std::make_shared<TileContainer>()});
    const auto Dirt = std::make_shared<Env>(TILE_SHEET_PATH, std::vector<std::shared_ptr<TileContainer>>{
            std::make_shared<TileContainer>()});


}



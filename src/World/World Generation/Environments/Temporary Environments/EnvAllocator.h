#pragma once

#include <array>
#include <memory>
#include "../../Tiles/TileMap.h"
#include "EnvBorderCorner.h"

class EnvWrapper;

class CompleteEnv;

class NeighboredEnv;

struct EnvAllocator {

    // + 2 for each row/col is to accommodate neighboring chunks' envs
    typedef std::array<std::array<std::shared_ptr<EnvWrapper>, TileMap::SIZE_X + 2>, TileMap::SIZE_Y + 2> EnvMap;
    typedef std::array<std::array<std::shared_ptr<NeighboredEnv>, TileMap::SIZE_Y + 2>,
            TileMap::SIZE_X + 2> TmpNeighboredEnvs;
    typedef std::array<std::array<std::shared_ptr<NeighboredEnv>, TileMap::SIZE_Y>,
            TileMap::SIZE_X> FinalNeighboredEnvs;

    static FinalNeighboredEnvs allocateEnvs(const EnvMap &initialEnvs);

    // Intended for testing purposes
    static void allocateCorners(const EnvMap &initialEnvs, TmpNeighboredEnvs &finalEnvs);

    static void allocateSharedSides(const EnvMap &initialEnvs, TmpNeighboredEnvs &finalEnvs);

    static void allocateInnerCells(const EnvMap &initialEnvs, TmpNeighboredEnvs &finalEnvs);

    static std::shared_ptr<NeighboredEnv>
    getEnvFromNeighbors(const std::shared_ptr<EnvWrapper> &initialEnv, const sf::Vector2i &coords,
                        const EnvAllocator::TmpNeighboredEnvs &finalEnvs);

    static struct {
        bool operator()(const std::shared_ptr<NeighboredEnv> &a, const std::shared_ptr<NeighboredEnv> &b) const {
            auto aCornerCasted = dynamic_cast<EnvBorderCorner *>(a.get());
            if (aCornerCasted != nullptr) {
                return true;
            }
            return false;
        }
    } candidateCompare;
};







#include <iostream>
#include "EnvAllocator.h"
#include "EnvWrapper.h"
#include "../CompleteEnv.h"


// Places possibleCandidate in tempCandidates if it is found in candidates
void updateTempCandidates(NeighboredEnv::Neighbors &candidates,
                          const std::shared_ptr<NeighboredEnv> &possibleCandidate,
                          NeighboredEnv::Neighbors &tempCandidates) {
    for (auto &candidate : candidates) {
        if (candidate->handleEquality(possibleCandidate)) {
            tempCandidates.push_back(candidate);
            return;
        }
    }

}

// Assume candidates is not empty, else returns nullptr
// Prioritization algorithm: select the copmleteenv version of initialEnv, if not exists, try to select a corner
//
std::shared_ptr<NeighboredEnv>
selectCandidate(const std::shared_ptr<EnvWrapper> &initialEnv, NeighboredEnv::Neighbors &candidates) {
    if (candidates.empty()) return nullptr; // this should never be reached

    std::sort(candidates.begin(), candidates.end(), EnvAllocator::candidateCompare);

    for (const auto &candidate : candidates) {
        if (*candidate == *initialEnv) {
            return initialEnv;
        }
        candidate->fillWildcardIfExists(initialEnv);
    }

    return candidates[0];
}

// Searches through adjacent neighbors, and determines NeighboredEnv type for initialEnv
std::shared_ptr<NeighboredEnv>
EnvAllocator::getEnvFromNeighbors(const std::shared_ptr<EnvWrapper> &initialEnv, const sf::Vector2i &coords,
                                  const EnvAllocator::TmpNeighboredEnvs &finalEnvs) {
    using namespace constants;

    NeighboredEnv::Neighbors candidates{}; // impossible to use set due to wildcard hashing
    bool noDirSeenYet = true;

    const std::vector<sf::Vector2i> adjacentDirections{NORTH, SOUTH, WEST, EAST};
    for (auto dir : adjacentDirections) {
        const sf::Vector2i neighborCoords{dir.x + coords.x, coords.y - dir.y};
        if (neighborCoords.x < 0 || neighborCoords.x >= finalEnvs.size() || neighborCoords.y < 0 ||
            neighborCoords.y >= finalEnvs.size() || finalEnvs[neighborCoords.x][neighborCoords.y] == nullptr)
            continue;


        auto currentEnv = finalEnvs[neighborCoords.x][neighborCoords.y];
        sf::Vector2i invertedDir = {dir.x * -1, dir.y * -1};
        auto possibleCandidates = currentEnv->getCompatibleNeighbors(invertedDir);

//        std::cout << "getEnvFromNeighbors - neighbor " << dir.x << ", " << dir.y << std::endl;
        NeighboredEnv::Neighbors tempCandidates = {};
        for (const auto &possibleCandidate : possibleCandidates) {
            if (noDirSeenYet) { // will only run for first dir; todo: refactor above
                tempCandidates.push_back(possibleCandidate);
            } else {
                updateTempCandidates(candidates, possibleCandidate, tempCandidates);
            }
        }

        candidates = tempCandidates;
        noDirSeenYet = false;
    }

//    std::cout << "getEnvFromNeighbors - " << candidates.size() << " candidates " << std::endl;

    if (candidates.empty()) {
        // couldn't find an env the 4 neighbors agree on
        // todo: handle modifications for prev? - might have to pass it in
        return initialEnv;
    } else {
        return selectCandidate(initialEnv, candidates);
    }
}

// Generate all envs based on the topleft env
void allocateCorner(const sf::Vector2i &topLeft, const EnvAllocator::EnvMap &initialEnvs,
                    EnvAllocator::TmpNeighboredEnvs &finalEnvs) {
    int x = topLeft.x;
    int y = topLeft.y;
    finalEnvs[x][y] = initialEnvs[x][y];
    finalEnvs[x][y]->togglePriority();

    finalEnvs[x + 1][y] = EnvAllocator::getEnvFromNeighbors(initialEnvs[x + 1][y], {x + 1, y}, finalEnvs);
    finalEnvs[x + 1][y]->togglePriority();
    finalEnvs[x][y + 1] = EnvAllocator::getEnvFromNeighbors(initialEnvs[x][y + 1], {x, y + 1}, finalEnvs);
    finalEnvs[x][y + 1]->togglePriority();
    finalEnvs[x + 1][y + 1] = EnvAllocator::getEnvFromNeighbors(initialEnvs[x + 1][y + 1], {x + 1, y + 1}, finalEnvs);
    finalEnvs[x + 1][y + 1]->togglePriority();
}

// Allocate Envs of all 4 corners of the temp matrix (ie. the 4 intersections of the
// adjacent chunks' corner tile Envs)
// Note: This function assumes Chunks/TileMaps are at least 4x4 tiles
void EnvAllocator::allocateCorners(const EnvMap &initialEnvs, TmpNeighboredEnvs &finalEnvs) {
    const int maxCornerTopLeftX = static_cast<int>(finalEnvs.size() - 2);
    const int maxCornerTopLeftY = static_cast<int>(finalEnvs[0].size() - 2);
    std::array<sf::Vector2i, 4> corners{sf::Vector2i{0, 0}, sf::Vector2i{maxCornerTopLeftX, maxCornerTopLeftY},
                                        sf::Vector2i{0, maxCornerTopLeftY}, sf::Vector2i{maxCornerTopLeftX, 0}};
    for (auto corner : corners) {
        allocateCorner(corner, initialEnvs, finalEnvs);
    }
}

// For columns shared between different chunks
void allocateColumn(const EnvAllocator::EnvMap &initialEnvs, EnvAllocator::TmpNeighboredEnvs &finalEnvs,
                    sf::Vector2i bottom, sf::Vector2i top, bool isPriority = false) {
    top.y++;
    bottom.y--;
    while (top.y <= bottom.y) {
        if (top == bottom) {
            finalEnvs[bottom.x][bottom.y] = EnvAllocator::getEnvFromNeighbors(initialEnvs[bottom.x][bottom.y],
                                                                              {bottom.x, bottom.y},
                                                                              finalEnvs);
            if (isPriority) finalEnvs[bottom.x][bottom.y]->togglePriority();
        } else {
            finalEnvs[top.x][top.y] = EnvAllocator::getEnvFromNeighbors(initialEnvs[top.x][top.y], {top.x, top.y},
                                                                        finalEnvs);
            if (isPriority) finalEnvs[top.x][top.y]->togglePriority();

            finalEnvs[bottom.x][bottom.y] = EnvAllocator::getEnvFromNeighbors(initialEnvs[bottom.x][bottom.y],
                                                                              {bottom.x, bottom.y},
                                                                              finalEnvs);
            if (isPriority) finalEnvs[bottom.x][bottom.y]->togglePriority();
        }
        top.y++;
        bottom.y--;
    }
}

// For rows shared between different chunks
void allocateRow(const EnvAllocator::EnvMap &initialEnvs, EnvAllocator::TmpNeighboredEnvs &finalEnvs,
                 sf::Vector2i right, sf::Vector2i left, bool isPriority = false) {
    right.x--;
    left.x++;
    while (left.x <= right.x) {
        if (left == right) {
            finalEnvs[right.x][right.y] = EnvAllocator::getEnvFromNeighbors(initialEnvs[right.x][right.y],
                                                                            {right.x, right.y},
                                                                            finalEnvs);
            if (isPriority) finalEnvs[right.x][right.y]->togglePriority();
        } else {
            finalEnvs[left.x][left.y] = EnvAllocator::getEnvFromNeighbors(initialEnvs[left.x][left.y], {left.x, left.y},
                                                                          finalEnvs);
            if (isPriority) finalEnvs[left.x][left.y]->togglePriority();

            finalEnvs[right.x][right.y] = EnvAllocator::getEnvFromNeighbors(initialEnvs[right.x][right.y],
                                                                            {right.x, right.y},
                                                                            finalEnvs);
            if (isPriority) finalEnvs[right.x][right.y]->togglePriority();
        }
        right.x--;
        left.x++;
    }
}

void
EnvAllocator::allocateSharedSides(const EnvAllocator::EnvMap &initialEnvs, EnvAllocator::TmpNeighboredEnvs &finalEnvs) {
    const int maxCornerTopLeftX = static_cast<int>(finalEnvs.size() -
                                                   2); // make the class stateful and store this in ctor?
    const int maxCornerTopLeftY = static_cast<int>(finalEnvs[0].size() - 2);

    sf::Vector2i top = {0, 1};
    sf::Vector2i bottom = {0, maxCornerTopLeftY};
    allocateColumn(initialEnvs, finalEnvs, bottom, top, true);
    allocateColumn(initialEnvs, finalEnvs, {bottom.x + 1, bottom.y}, {top.x + 1, top.y}, true);

    top.x = maxCornerTopLeftX;
    bottom.x = top.x;
    allocateColumn(initialEnvs, finalEnvs, bottom, top, true);
    allocateColumn(initialEnvs, finalEnvs, {bottom.x + 1, bottom.y}, {top.x + 1, top.y}, true);


    sf::Vector2i left = {1, 0};
    sf::Vector2i right = {maxCornerTopLeftX, 0};
    allocateRow(initialEnvs, finalEnvs, right, left, true);
    allocateRow(initialEnvs, finalEnvs, {right.x, right.y + 1}, {left.x, left.y + 1}, true);

    left.y = maxCornerTopLeftY;
    right.y = left.y;
    allocateRow(initialEnvs, finalEnvs, right, left, true);
    allocateRow(initialEnvs, finalEnvs, {right.x, right.y + 1}, {left.x, left.y + 1}, true);
}

void recordEnvFrequency(std::unordered_map<const Env *, int> &frequencies, const Env *env) {
    if (env == nullptr) return;
    if (frequencies.count(env) == 0) {
        frequencies.insert({env, 1});
    } else {
        auto curFreq = frequencies[env];
        frequencies.insert({env, curFreq + 1});
    }
}

const Env *findEnvWithMaxFrequency(std::unordered_map<const Env *, int> &envFrequencies) {
    const Env *maxEnv;
    int maxFreq = INT_MIN;
    for (auto const&[key, val] : envFrequencies) {
        if (val > maxFreq) {
            maxEnv = key;
        }
    }
    return maxEnv;
}

// DominantEnv = most frequently appearing env including both sides of border cells
std::shared_ptr<EnvWrapper> computeDominantEnvFromSharedCells(EnvAllocator::TmpNeighboredEnvs &finalEnvs) {
    // need a polymorphic method of resolving which env * are associated to a n
    int sizeX = static_cast<int>(finalEnvs.size());
    int sizeY = static_cast<int>(finalEnvs[0].size());
    std::unordered_map<const Env *, int> envFrequencies;

    for (auto x = 0; x < sizeX - 1; x++) {
        auto envs = finalEnvs[x][0]->getEnvs();
        recordEnvFrequency(envFrequencies, envs.first);
        recordEnvFrequency(envFrequencies, envs.second);
    }

    for (auto x = 0; x < sizeX - 1; x++) {
        auto envs = finalEnvs[x][sizeY - 1]->getEnvs();
        recordEnvFrequency(envFrequencies, envs.first);
        recordEnvFrequency(envFrequencies, envs.second);
    }

    for (auto y = 0; y < sizeY - 1; y++) {
        auto envs = finalEnvs[0][y]->getEnvs();
        recordEnvFrequency(envFrequencies, envs.first);
        recordEnvFrequency(envFrequencies, envs.second);
    }

    for (auto y = 0; y < sizeY - 1; y++) {
        auto envs = finalEnvs[sizeX - 1][y]->getEnvs();
        recordEnvFrequency(envFrequencies, envs.first);
        recordEnvFrequency(envFrequencies, envs.second);
    }

    const Env *mostFrequentEnv = findEnvWithMaxFrequency(envFrequencies);
    return std::make_shared<EnvWrapper>(mostFrequentEnv);
}


void
EnvAllocator::allocateInnerCells(const EnvAllocator::EnvMap &initialEnvs, EnvAllocator::TmpNeighboredEnvs &finalEnvs) {
    int sizeX = static_cast<int>(initialEnvs.size());
    int sizeY = static_cast<int>(initialEnvs[0].size());

//    auto dominantEnv = computeDominantEnvFromSharedCells(finalEnvs);
//
//    for (auto x = 3; x < sizeX - 3;  x++) {
//        for (auto y = 3; y < sizeY - 3; y++) {
//            finalEnvs[x][y] = dominantEnv; // WARNING: if EnvWrapper becomes mutable, this will cause issues
//        }
//    }
//
//    // allocate 3rd row/col and 3rd from last row/col
//    sf::Vector2i bottom{2, sizeY - 2};
//    sf::Vector2i top{2, 1};
//    allocateColumn(initialEnvs, finalEnvs, bottom, top);
//
//    bottom.x = sizeX - 3;
//    top.x = bottom.x;
//    allocateColumn(initialEnvs, finalEnvs, bottom, top);
//
//    sf::Vector2i right{sizeX - 2, 2};
//    sf::Vector2i left{1, 2};
//    allocateRow(initialEnvs, finalEnvs, right, left);
//
//    right.y = sizeY - 3;
//    left.y = right.y;
//    allocateRow(initialEnvs, finalEnvs, right, left);

    sf::Vector2i bottom{2, sizeY - 2};
    sf::Vector2i top{2, 1};

    while (top.x < sizeX - 2) {
        allocateColumn(initialEnvs, finalEnvs, bottom, top);
        top.x++;
        bottom.x++;
    }
}

EnvAllocator::FinalNeighboredEnvs resizeFinalEnvs(const EnvAllocator::TmpNeighboredEnvs &finalEnvs) {
    EnvAllocator::FinalNeighboredEnvs result;
    for (int x = 0; x < result.size(); x++) {
        for (int y = 0; y < result[0].size(); y++) {
            result[x][y] = finalEnvs[x + 1][y + 1];
        }
    }
    return result;
}

EnvAllocator::FinalNeighboredEnvs EnvAllocator::allocateEnvs(const EnvMap &initialEnvs) {
    TmpNeighboredEnvs tmpNeighboredEnvs;
    allocateCorners(initialEnvs, tmpNeighboredEnvs);
    allocateSharedSides(initialEnvs, tmpNeighboredEnvs);
    allocateInnerCells(initialEnvs, tmpNeighboredEnvs);

    return resizeFinalEnvs(tmpNeighboredEnvs);
}

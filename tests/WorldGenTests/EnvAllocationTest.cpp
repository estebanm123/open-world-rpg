
#define CATCH_CONFIG_FAST_COMPILE

#include "../catch.hpp"
#include "../../src/World/World Generation/Environments/Temporary Environments/EnvAllocator.h"
#include "../../src/World/World Generation/Environments/Temporary Environments/EnvWrapper.h"
#include "../../src/World/World Generation/Environments/EnvTypes.h"
#include "../../src/World/World Generation/Environments/Temporary Environments/EnvBorderCorner.h"
#include "../../src/World/World Generation/Environments/Temporary Environments/EnvBorderVertical.h"
#include "../../src/World/World Generation/Environments/Temporary Environments/EnvBorderHorizontal.h"
#include "../../src/World/World Generation/Environments/EnvSelector.h"

#include <iostream>


using namespace EnvTypes;

auto dirt = std::make_shared<EnvWrapper>(nullptr);
auto water = std::make_shared<EnvWrapper>(nullptr);


typedef EnvAllocator::TmpNeighboredEnvs ResultEnvs;


// ---------------------
// Helpers
// ---------------------

// todo: just use function abstracted from a lib file
sf::Vector2f convertLocalToGlobalCoords_(sf::Vector2i localCoords, sf::Vector2f globalPos) {
    auto localCoordsFloat = static_cast<sf::Vector2f>(localCoords); // safe cast, as localCoords will never be very high
    sf::Vector2f relativePosition{localCoordsFloat.x * worldConstants::TILE_SIZE.x,
                                  localCoordsFloat.y * worldConstants::TILE_SIZE.y};
    return globalPos + relativePosition;
}

void mockInitialEnvGeneration(EnvAllocator::EnvMap &initialEnvs, const sf::Vector2f &pos) {
    for (int x = 0; x < initialEnvs.size(); x++) {
        for (int y = 0; y < initialEnvs[0].size(); y++) {
            sf::Vector2i localCoords{x, y};
            auto globalCoords = convertLocalToGlobalCoords_(localCoords, pos);
            const auto environment = EnvSelector::getEnvironment(globalCoords);
            initialEnvs[x][y] = std::make_shared<EnvWrapper>(environment);
        }
    }
}

char STR_SIZE = 12;

void pad(std::string &x) {
    while (x.length() < 12) {
        x += ' ';
    }
}

std::string ptrStr(const std::shared_ptr<NeighboredEnv> &ptr) {
    return ptr == nullptr ? "" : ptr->toString();
}

// todo: maybe make it configurable to only check
// a subset square of the matrix + add option to disable printing
// Helper for checking the equality of matrix + printing
bool printResultEnvs(const ResultEnvs &actual, const ResultEnvs &expected = ResultEnvs()) {
    bool equal = true;

    for (int y = 0; y < actual[0].size(); y++) {
        for (int x = 0; x < actual.size(); x++) {

            auto result =
                    std::to_string(x) + "," + std::to_string(y) + ptrStr(actual[x][y]) + "=" + ptrStr(expected[x][y]);
            pad(result);
            std::cout << "|" << result;

            if ((actual[x][y] == nullptr && expected[x][y] != nullptr) ||
                (actual[x][y] != nullptr && expected[x][y] == nullptr)) {
                equal = false;
                continue;
            } else if (actual[x][y] == nullptr && expected[x][y] == nullptr) {
                continue;
            }


            if (!(*actual[x][y] == *expected[x][y])) { // operator overloaded
                equal = false;
            }
        }
        std::cout << std::endl;
    }
    return equal;
}


void printEnvBorderDetails(const std::shared_ptr<NeighboredEnv> &env) {
    const auto borderEnv = dynamic_cast<EnvBorderData *>(env.get());
    if (borderEnv == nullptr || !borderEnv->primaryEnv || !borderEnv->secondaryEnv) return;
    std::cout << "== dirt?" << (*borderEnv->primaryEnv == *dirt) << "-" << (*borderEnv->secondaryEnv == *dirt)
              << std::endl;
}



// ---------------------------
// North + east neighbor tests
// ---------------------------

TEST_CASE("getEnvFromNeighbors - 2x corner; dirt dominance") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = std::make_shared<EnvBorderCorner>(dirt, water, 270);
    finalEnvs[1][0] = std::make_shared<EnvBorderCorner>(dirt, water, 270);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 1}, finalEnvs);
    const EnvBorderCorner expected1(water, dirt, 90);

    bool success = (expected1 == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - vertical + horizontal; water dominance 2") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = std::make_shared<EnvBorderHorizontal>(dirt, water);
    finalEnvs[1][0] = std::make_shared<EnvBorderVertical>(water, dirt);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 1}, finalEnvs);
    const EnvBorderCorner expected1(water, dirt, 90);

    bool success = (expected1 == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - corner + horizontal; mixed dominance") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = std::make_shared<EnvBorderHorizontal>(dirt, water);
    finalEnvs[1][0] = std::make_shared<EnvBorderCorner>(water, dirt, 180);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 1}, finalEnvs);
    const EnvBorderCorner expected1(water, dirt, 90);

    bool success = (expected1 == *result);
    REQUIRE(success);
}


TEST_CASE("getEnvFromNeighbors - all full water") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = water;
    finalEnvs[1][0] = water;
    const auto result = EnvAllocator::getEnvFromNeighbors(water, {1, 1}, finalEnvs);
    bool success = (*water == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - 2 full waters; water dominant") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = water;
    finalEnvs[1][0] = water;
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 1}, finalEnvs);

    printEnvBorderDetails(result);

    const EnvBorderCorner expected1(water, dirt, 270);


    bool success = (expected1 == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - horizontal + vertical; dirt dominant") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = std::make_shared<EnvBorderVertical>(dirt, water);
    finalEnvs[1][0] = std::make_shared<EnvBorderHorizontal>(water, dirt);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 1}, finalEnvs);

    bool success = (*dirt == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - 2x corners; water dominant 1") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = std::make_shared<EnvBorderCorner>(water, dirt, 0);
    finalEnvs[1][0] = std::make_shared<EnvBorderCorner>(water, dirt, 180);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 1}, finalEnvs);
    const EnvBorderCorner expected1(water, dirt, 90);

    bool success = (expected1 == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - corner + vertical; water dominant") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = std::make_shared<EnvBorderVertical>(water, dirt);
    finalEnvs[1][0] = std::make_shared<EnvBorderCorner>(water, dirt, 270);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 1}, finalEnvs);
    const EnvBorderCorner expected1(water, dirt, 0);
    const EnvBorderVertical expected2(dirt, water);

    bool success = (expected1 == *result) || (expected2 == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - 2x corners; water dominant") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[2][1] = std::make_shared<EnvBorderCorner>(water, dirt, 180);
    finalEnvs[1][0] = std::make_shared<EnvBorderCorner>(water, dirt, 270);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 1}, finalEnvs);
    const EnvBorderCorner expected1(water, dirt, 0);
    const EnvBorderVertical expected2(dirt, water);

    bool success = (expected1 == *result) || (expected2 == *result);
    REQUIRE(success);
}
// --------------------------
// South + west neighbor tests
// --------------------------

TEST_CASE("getEnvFromNeighbors - 2x vertical; dirt dominant") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[0][0] = std::make_shared<EnvBorderVertical>(water, dirt);
    finalEnvs[1][1] = std::make_shared<EnvBorderVertical>(dirt, water);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 0}, finalEnvs);
    const EnvBorderCorner expected1(dirt, water, 180);
    const EnvBorderVertical expected2(dirt, water);

    bool success = (expected1 == *result) || (expected2 == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - Full + vertical; dirt dominant") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[0][0] = dirt;
    finalEnvs[1][1] = std::make_shared<EnvBorderVertical>(dirt, water);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 0}, finalEnvs);
    const EnvBorderCorner expected1(dirt, water, 180);
    const EnvBorderVertical expected2(dirt, water);

    bool success = (expected1 == *result) || (expected2 == *result);
    REQUIRE(success);
}

TEST_CASE("getEnvFromNeighbors - Horizontal + vertical combo 1") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[0][0] = std::make_shared<EnvBorderVertical>(dirt, water);
    finalEnvs[1][1] = std::make_shared<EnvBorderHorizontal>(water, dirt);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 0}, finalEnvs);
    const EnvBorderCorner expected(water, dirt, 90);

    REQUIRE(expected == *result);
}

TEST_CASE("getEnvFromNeighbors - Corner 1") {
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    finalEnvs[0][0] = std::make_shared<EnvBorderCorner>(dirt, water, 90);
    finalEnvs[1][1] = std::make_shared<EnvBorderCorner>(dirt, water, 90);
    const auto result = EnvAllocator::getEnvFromNeighbors(dirt, {1, 0}, finalEnvs);
    const EnvBorderCorner expected(water, dirt, 270);

    REQUIRE(expected == *result);
}

//TEST_CASE("Corners - all same type") {
//    EnvAllocator::EnvMap initialMap;
//    for (int x = 0; x < initialMap.size(); x++) {
//        for (int y = 0; y < initialMap[0].size(); y++) {
//            initialMap[x][y] = dirt;
//        }
//    }
//
//    EnvAllocator::TmpNeighboredEnvs actualMap;
//    EnvAllocator::allocateCorners(initialMap, actualMap);
//
//    EnvAllocator::TmpNeighboredEnvs expectedMap;
//    for (int x = 0; x < initialMap.size(); x++) {
//        for (int y = 0; y < initialMap[0].size(); y++) {
//            expectedMap[x][y] = dirt;
//        }
//    }
//
//    // refactor with a require
//    CHECK(checkEquality(actualMap, expectedMap));
//

// ------------------------------------------------
// Visual tests
// ------------------------------------------------

void testCompleteAllocation(sf::Vector2f coords) {
    EnvAllocator::EnvMap initialEnvs;
    mockInitialEnvGeneration(initialEnvs, coords);
    EnvAllocator::TmpNeighboredEnvs finalEnvs;
    EnvAllocator::allocateCorners(initialEnvs, finalEnvs);
    EnvAllocator::allocateSharedSides(initialEnvs, finalEnvs);
    EnvAllocator::allocateInnerCells(initialEnvs, finalEnvs);

    printResultEnvs(finalEnvs);

}

void setup() {
    EnvTypes::initialize();
    dirt = std::make_shared<EnvWrapper>(EnvManager::getEnv(DIRT));
    water = std::make_shared<EnvWrapper>(EnvManager::getEnv(WATER));
}

TEST_CASE("Visual - test allocation of priority cells") {
    setup();
    testCompleteAllocation({10000, -10000001});
}


TEST_CASE("Visual - test allocation of priority cells 4 ") {
    setup();
    testCompleteAllocation({0, 0});
}

TEST_CASE("Visual - test allocation of priority cells 2 ") {
    setup();
    testCompleteAllocation({1000001, -1000001});
}

TEST_CASE("Visual - test allocation of priority cells 3 ") {
    setup();
    testCompleteAllocation({-32345678, -1001});
}

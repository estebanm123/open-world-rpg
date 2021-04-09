//
//#include "PropFactory.h"
//#include "../Prop.h"
//#include "../../../../../Animation/RepeatingAnim.h"
//
//
//std::unique_ptr<Prop> PropFactory::initialize(const sf::Vector2f &propCoords, bool isDecor) {
//    auto hashVal = hash2ValuesModSize(propCoords.x, propCoords.y, HASH_LIM);
//    return isDecor ? generateDecorProp(hashVal, propCoords) : generateMainProp(hashVal, propCoords);
//}
//
//int PropFactory::normalizeHashValue(int hashVal, int minimum) {
//    auto relativeUpperBound = static_cast<float>(HASH_LIM - minimum);
//    auto relativeHashVal = static_cast<float>(hashVal - minimum);
//    float proportionOfRelativeZone = relativeHashVal / relativeUpperBound;
//    return static_cast<int>(proportionOfRelativeZone * HASH_LIM); // reset as proportion to HASH_LIM
//}
//
//int PropFactory::getPropIndex(int hashVal, int numProps) {
//    return hashVal % numProps;
//}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ------ ASSETS -------------
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~

//
//const std::array<sf::IntRect, 4> ROCK_SPRITESPRITES{{
//                                                            {0, 0, 29, 28},
//                                                            {29, 0, 52, 52},
//                                                            {81, 0, 25, 29},
//                                                            {106, 0, 29, 29}
//                                                    }};
//
//std::unique_ptr<Prop> PropFactory::generateRock(int hashVal, const sf::Vector2f &pos) {
//    int selectedIndex = getPropIndex(hashVal, ROCK_SPRITESPRITES.size());
//    const auto &spriteSheetCoords = ROCK_SPRITESPRITES[selectedIndex];
//    const sf::Vector2f size = {static_cast<float>(spriteSheetCoords.width - SIZE_FLEX),
//                               static_cast<float>(spriteSheetCoords.height - SIZE_FLEX)};
//    return std::make_unique<Prop>("Foliage/Shadow/Rocks", size, spriteSheetCoords,
//                                  Prop::PropOptions{pos, true, std::make_unique<BlockingPhysics>()});
//}
//
//const std::array<sf::IntRect, 1> BUSH_SPRITESPRITES{{
//                                                            {0, 0, 36, 32}
//                                                    }};
//
//
//std::unique_ptr<Prop> PropFactory::generateBush(int hashVal, const sf::Vector2f &pos) {
//    int selectedIndex = getPropIndex(hashVal, BUSH_SPRITESPRITES.size());
//    const auto &spriteSheetCoords = BUSH_SPRITESPRITES[selectedIndex];
//    const sf::Vector2f size = {static_cast<float>(spriteSheetCoords.width - SIZE_FLEX),
//                               static_cast<float>(spriteSheetCoords.height - SIZE_FLEX)};
//    int delay = 200;
//    int start = 0;
//    int end = 2;
//    Animation::Metadata data(spriteSheetCoords.width, spriteSheetCoords.height, start, end, 0, delay, {});
//    return std::make_unique<Prop>("Foliage/Shadow/ForestFoliage", size, spriteSheetCoords,
//                                  Prop::PropOptions{pos, true, std::make_unique<BlockingPhysics>(),
//                                                    std::make_unique<AnimationPlayer>(
//                                                            std::make_unique<RepeatingAnim>(data))});
//}
//
//
//
//std::unique_ptr<Prop> PropFactory::generateGrassCover(int hashVal, const sf::Vector2f &pos) {
//    int selectedIndex = getPropIndex(hashVal, GRASS_COVER_SPRITES.size());
//    const auto &spriteSheetCoords = GRASS_COVER_SPRITES[selectedIndex];
//    const sf::Vector2f size = {static_cast<float>(spriteSheetCoords.width),
//                               static_cast<float>(spriteSheetCoords.height)};
//    return std::make_unique<Prop>("Foliage/GrassOverlays", size, spriteSheetCoords,
//                                  Prop::PropOptions{pos});
//}
//
//const std::array<sf::IntRect, 1> MUSHROOM_SPRITES{{
//                                                          {0, 0, 22, 20},
//                                                  }};
//
//std::unique_ptr<Prop> PropFactory::generateMushrooms(int hashVal, const sf::Vector2f &pos) {
//    int selectedIndex = getPropIndex(hashVal, MUSHROOM_SPRITES.size());
//    const auto &spriteSheetCoords = MUSHROOM_SPRITES[selectedIndex];
//    const sf::Vector2f size = {static_cast<float>(spriteSheetCoords.width),
//                               static_cast<float>(spriteSheetCoords.height)};
//    return std::make_unique<Prop>("Foliage/Shadow/Mushroom", size, spriteSheetCoords,
//                                  Prop::PropOptions{pos, true});
//}
//
//const std::array<sf::IntRect, 1> CACTUS_SHEET{{
//                                                      {0, 0, 22, 20},
//                                              }};
//
//std::unique_ptr<Prop> PropFactory::generateCactus(int hashVal, const sf::Vector2f &pos) {
//    int selectedIndex = getPropIndex(hashVal, CACTUS_SHEET.size());
//    const auto &spriteSheetCoords = CACTUS_SHEET[selectedIndex];
//    const sf::Vector2f size = {static_cast<float>(spriteSheetCoords.width),
//                               static_cast<float>(spriteSheetCoords.height)};
//    return std::make_unique<Prop>("Foliage/Shadow/Cactus", size, spriteSheetCoords,
//                                  Prop::PropOptions{pos, true, std::make_unique<BlockingPhysics>()});
//
//}

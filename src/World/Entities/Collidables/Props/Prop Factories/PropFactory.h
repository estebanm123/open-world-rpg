#pragma once


#include <SFML/Graphics.hpp>

class Prop;

class PropFactory {
public:
    std::unique_ptr<Prop> generateProp(const sf::Vector2f &propCoords);

    virtual std::unique_ptr<Prop> generateProp(int hashVal, const sf::Vector2f &propCoords) = 0;

protected:
    static constexpr auto HASH_LIM = 100;


    // Normalizes hashVal relative to minimum, and recomputes this as a fraction of HASH_LIM
    // It's important to standardize the bounds of the hashVal, so super classes know what to expect
    // when their 'generate__' functions are called and supports HASH_LIM's full spectrum of values.
    static int normalizeHashValue(int hashVal, int minimum);

    static int getPropIndex(int hashVal, int numProps);

    // hashVal must be between 0 - HASH_LIM
    virtual std::unique_ptr<Prop> generateRocks(int hashVal, const sf::Vector2f &propCoords);

    std::unique_ptr<Prop> generateRock(const sf::Vector2f &pos, const sf::IntRect &spriteSheetCoords);

//    virtual std::unique_ptr<Prop> generateBushes(int hashVal, const sf::Vector2f &propCoords);
};






#pragma once


#include <SFML/Graphics.hpp>

class Prop;
class InteractiveProp;
class DecorProp;

class PropFactory {
public:
    std::unique_ptr<InteractiveProp> generateInteractiveProp(const sf::Vector2f &propCoords);

    std::unique_ptr<DecorProp> generateDecorProp(const sf::Vector2f &propCoords);

    virtual std::unique_ptr<InteractiveProp> generateInteractiveProp(int hashVal, const sf::Vector2f &propCoords) = 0;

    virtual std::unique_ptr<DecorProp> generateDecorProp(int hashVal, const sf::Vector2f &propCoords) = 0;

protected:
    static constexpr auto HASH_LIM = 100;


    // Normalizes hashVal relative to minimum, and recomputes this as a fraction of HASH_LIM
    // It's important to standardize the bounds of the hashVal, so super classes know what to expect
    // when their 'generate__' functions are called and supports HASH_LIM's full spectrum of values.
    static int normalizeHashValue(int hashVal, int minimum);

    static int getPropIndex(int hashVal, int numProps);

    // hashVal must be between 0 - HASH_LIM
    virtual std::unique_ptr<InteractiveProp> generateRocks(int hashVal, const sf::Vector2f &propCoords);

    // todo: make more abstract for others (make a callable helper for helpers)
    // todo: update for destructible environment
    std::unique_ptr<InteractiveProp> generateRock(const sf::Vector2f &pos, const sf::IntRect &spriteSheetCoords);
};






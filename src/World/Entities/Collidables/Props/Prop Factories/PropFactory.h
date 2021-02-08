#pragma once


#include <SFML/Graphics.hpp>

class Prop;

class PropFactory {
public:
    std::unique_ptr<Prop> generateProp(const sf::Vector2f &propCoords, bool isDecor);

    virtual std::unique_ptr<Prop> generateMainProp(int hashVal, const sf::Vector2f &propCoords) = 0;

    virtual std::unique_ptr<Prop> generateDecorProp(int hashVal, const sf::Vector2f &propCoords) = 0;

protected:
    static constexpr auto HASH_LIM = 100;

    // Normalizes hashVal relative to minimum, and recomputes this as a fraction of HASH_LIM
    // It's important to standardize the bounds of the hashVal, so super classes know what to expect
    // when their 'generate__' functions are called and supports HASH_LIM's full spectrum of values.
    static int normalizeHashValue(int hashVal, int minimum);

    static int getPropIndex(int hashVal, int numProps);

    // hashVal must be between 0 - HASH_LIM
    std::unique_ptr<Prop> generateRock(int hashVal, const sf::Vector2f &pos);

    std::unique_ptr<Prop> generateBush(int hashVal, const sf::Vector2f &pos);

    std::unique_ptr<Prop> generateGrassCover(int hashVal, const sf::Vector2f &pos);

};






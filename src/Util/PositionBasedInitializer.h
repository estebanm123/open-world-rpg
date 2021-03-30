#pragma once

#include <memory>
#include <SFML/Audio.hpp>

template<class T>
class PositionBasedInitializer {
public:
    typedef sf::Vector2f Position;

    virtual std::unique_ptr<T> initialize(Position pos) = 0;
};





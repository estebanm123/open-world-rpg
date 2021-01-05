#pragma once

#include <memory>
#include <vector>

class TileMap;
class DecorProp;
class InteractiveProp;


class ChunkPropGenerator {
public:
    static std::vector<std::unique_ptr<InteractiveProp>> generateInteractiveProps(const TileMap & tileMap);
    static std::vector<std::unique_ptr<DecorProp>> generateDecorProps(const TileMap & tileMap);
private:
    static constexpr float PROP_CHANCE_MAX = 100;
    static constexpr float PROP_CHANCE = 20;
    static constexpr float PROP_CHANCE_CHANGE = 3;
};



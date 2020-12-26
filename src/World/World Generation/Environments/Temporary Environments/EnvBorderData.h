#pragma once

#include "NeighboredEnv.h"
#include <SFML/System.hpp>
#include <memory>
#include "../../../../Util/Constants.h"

class EnvWrapper;

class Env;
class SingleTileContainer;

struct EnvBorderData : public NeighboredEnv {
    EnvBorderData(const std::shared_ptr<EnvWrapper> & primary, const std::shared_ptr<EnvWrapper> & secondary);
    std::shared_ptr<EnvWrapper> primaryEnv;
    std::shared_ptr<EnvWrapper> secondaryEnv;

    bool operator==(const NeighboredEnv & other) const override;

    bool handleEquality(const std::shared_ptr<NeighboredEnv> & other) override;

    const NeighboredEnv::TileContainerWrapper extractTileMetadata(const sf::Vector2f &globalCoords) const override;

    // Rotation angle of the border
    virtual float getExtraRotationAngle() const;

    bool fillWildcardIfExists(const std::shared_ptr<EnvWrapper> & filler) override;

    ~EnvBorderData() override = default;
protected:
    virtual const SingleTileContainer * getTileContainer(const Env * primary, const Env * secondary) const;
};

namespace std
{
    using namespace constants;
    template<>
    struct hash<EnvBorderData>
    {
        size_t operator()(const EnvBorderData& x) const
        {
            size_t result = 1;
            result = result * HASH_PRIME + (size_t) x.primaryEnv.get();
            result = result * HASH_PRIME + (size_t) x.secondaryEnv.get();
            return result;
        }
    };

    template<>
    struct hash<shared_ptr<EnvBorderData>>
    {
        size_t operator()(const shared_ptr<EnvBorderData>& x) const
        {
            std::hash<EnvBorderData> h;
            return h(*x);
        }
    };
}



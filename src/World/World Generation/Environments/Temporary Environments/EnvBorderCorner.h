#pragma once
#include "EnvBorderData.h"

struct EnvBorderCorner : public EnvBorderData {
    EnvBorderCorner(const std::shared_ptr<EnvWrapper> & primary, const std::shared_ptr<EnvWrapper> & secondary, float rotationAngle = 0);

    NeighboredEnv::Neighbors getCompatibleNeighbors(const sf::Vector2i & direction) const override;

    bool handleEquality(const std::shared_ptr<NeighboredEnv> & other) override;

    float getExtraRotationAngle() const override;

    const SingleTileContainer * getTileContainer(const Env * primary, const Env * secondary) const override;

    bool operator==(const NeighboredEnv& other) const override;

    std::string toString() const override;

    float rotationAngle;

private:
    NeighboredEnv::Neighbors getNorthNeighbors() const;
    NeighboredEnv::Neighbors getSouthNeighbors() const;
    NeighboredEnv::Neighbors getWestNeighbors() const;
    NeighboredEnv::Neighbors getEastNeighbors() const;

};

namespace std
{
    using namespace constants;
    template<>
    struct hash<EnvBorderCorner>
    {
        size_t operator()(const EnvBorderCorner& x) const
        {
            size_t result = 1;
            result = result * HASH_PRIME + (size_t) x.primaryEnv.get();
            result = result * HASH_PRIME + (size_t) x.secondaryEnv.get();
            result = result * HASH_PRIME + x.rotationAngle;
            return result;
        }
    };
    template<>
    struct hash<shared_ptr<EnvBorderCorner>>
    {
        size_t operator()(const shared_ptr<EnvBorderCorner>& x) const
        {
            std::hash<EnvBorderCorner> h;
            return h(*x);
        }
    };
}





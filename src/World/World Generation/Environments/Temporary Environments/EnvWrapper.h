#pragma once

#include "NeighboredEnv.h"
#include "../../../../Util/Constants.h"

class Env;

struct EnvWrapper : public NeighboredEnv {
    EnvWrapper(const Env * env);

    NeighboredEnv::Neighbors getCompatibleNeighbors(const sf::Vector2i &direction) const override;

    const TileContainerWrapper extractTileMetadata(const sf::Vector2f &globalCoords) const override;

    bool handleEquality(const std::shared_ptr<NeighboredEnv> &other) override;

    bool fillWildcardIfExists(const std::shared_ptr<EnvWrapper> &filler) override;

    const Env *getEnv() const;

    bool operator==(const NeighboredEnv &other) const override;

    std::string toString() const override;

    const Env * env;
};

namespace std {
    using namespace constants;

    template<>
    struct hash<EnvWrapper> {
        size_t operator()(const EnvWrapper &x) const {
            size_t result = 1;
            result = result * HASH_PRIME + (size_t) &x.env;
            return result;
        }
    };

    template<>
    struct hash<shared_ptr<EnvWrapper>> {
        size_t operator()(const shared_ptr<EnvWrapper> &x) const {
            std::hash<EnvWrapper> h;
            return h(*x);
        }
    };
}






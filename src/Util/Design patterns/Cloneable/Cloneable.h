#pragma once

#include <memory>

// Inspired by Prototype pattern.
template<class CloneableSubType>
class Cloneable {
    virtual std::unique_ptr<CloneableSubType> clone() const = 0;
};





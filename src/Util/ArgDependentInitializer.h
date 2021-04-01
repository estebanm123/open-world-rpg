#pragma once

#include <memory>
#include <SFML/Audio.hpp>

template<class Output, typename Arg>
class ArgDependentInitializer {
public:
    virtual std::unique_ptr<Output> initialize(Arg pos) = 0;
};





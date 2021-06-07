#pragma once

#include <SFML/Audio.hpp>
#include <memory>

template <class Output, typename Arg>
class ArgDependentInitializer {
public:
	virtual std::unique_ptr<Output> initialize(Arg arg) = 0;
};

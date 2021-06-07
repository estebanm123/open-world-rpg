#pragma once

#include <SFML/System/NonCopyable.hpp>

struct NonMoveable {
	NonMoveable() = default;

	NonMoveable &operator=(sf::NonCopyable &&) = delete;

	NonMoveable(sf::NonCopyable &&) = delete;
};

#pragma once

struct NonMoveable {
    NonMoveable() = default;

    NonMoveable &operator=(sf::NonCopyable &&) = delete;

    NonMoveable(sf::NonCopyable &&) = delete;
};

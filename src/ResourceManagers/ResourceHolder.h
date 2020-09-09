#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"
#include "../Util/NonMoveable.h"

class ResourceHolder : public sf::NonCopyable, public NonMoveable
{
    public:
        static ResourceHolder& get();

        ResourceManager<sf::Font>           fonts;
        ResourceManager<sf::Texture>        textures;
        ResourceManager<sf::SoundBuffer>    soundBuffers;

    private:
        ResourceHolder();
};

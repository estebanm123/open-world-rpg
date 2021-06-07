#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../Util/NonMoveable.h"
#include "ResourceManager.h"

class ResourceHolder : public sf::NonCopyable, public NonMoveable {
public:
	static ResourceHolder &get();

	ResourceManager<sf::Font> fonts;
	ResourceManager<sf::Texture> textures;
	ResourceManager<sf::SoundBuffer> soundBuffers;

private:
	ResourceHolder();
};

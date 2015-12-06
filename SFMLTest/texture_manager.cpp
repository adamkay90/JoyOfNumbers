#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "texture_manager.h"

// Load an image from a filename
void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	/* Load the texture */
	sf::Texture tex;
	tex.loadFromFile(filename);

	/* Add it to the list of textures */
	this->textures[name] = tex;

	return;
}

// Return a texture from the texture map
sf::Texture& TextureManager::getRef(const std::string& texture)
{
	return this->textures.at(texture);
}
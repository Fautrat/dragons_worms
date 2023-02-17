#include "AssetManagerTemp.h"
#include <iostream>
#include "../Engine.h"

AssetManagerTemp* AssetManagerTemp::s_instance = nullptr;

AssetManagerTemp::AssetManagerTemp() {}

sf::Texture* AssetManagerTemp::getTexture(std::string id) {
	return (textures.count(id) > 0) ? textures[id] : nullptr;
}

void AssetManagerTemp::loadTexture(std::string id, std::string path) {
	if (textures.count(id) <= 0)
	{
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(path.c_str()))
		{
			std::cout << "Failed to load Texture : ["<< path << "]" << std::endl;
			return;
		}
		else
		{
			textures[id] = texture;
			std::cout << "Texture: [" << path << "] loaded !" << std::endl;
		}
		
	}
}

sf::Font* AssetManagerTemp::getFont(std::string id) {
	return (fonts.count(id) > 0) ? fonts[id] : nullptr;
}

void AssetManagerTemp::loadFont(std::string id, std::string path, int size) {
	if (fonts.count(id) <= 0)
	{
		sf::Font* font = new sf::Font();
		if (!font->loadFromFile(path.c_str()))
		{
			std::cout << "Failed to load Font : [" << path << "]" << std::endl;
			return;
		}
		else
		{
			fonts[id] = font;
			std::cout << "Font: [" << path << "] loaded !" << std::endl;
		}

	}
}

sf::Music* AssetManagerTemp::getMusic(std::string id) {
	return (musics.count(id) > 0) ? musics[id] : nullptr;
}

void AssetManagerTemp::loadMusic(std::string id, std::string path, int volume) {
	if (musics.count(id) <= 0)
	{
		sf::Music* music = new sf::Music();
		if (!music->openFromFile(path.c_str()))
		{
			std::cout << "Failed to load music : [" << path << "]" << std::endl;
			return;
		}
		else
		{
			musics[id] = music;
			std::cout << "Music: [" << path << "] loaded !" << std::endl;
		}

	}
}

void AssetManagerTemp::clean() {

	for (auto it = textures.begin(); it != textures.end(); it++) {
		textures.erase(it);
	}

	textures.clear();

	for (auto it = fonts.begin(); it != fonts.end(); it++) {
		fonts.erase(it);
	}

	fonts.clear();

	for (auto it = musics.begin(); it != musics.end(); it++) {
		musics.erase(it);
	}

	musics.clear();
	
}



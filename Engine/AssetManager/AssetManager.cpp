#include "AssetManager.h"
#include <iostream>
#include "../Engine.h"

AssetManager* AssetManager::s_instance = nullptr;

AssetManager::AssetManager() {}

sf::Texture* AssetManager::getTexture(std::string id) {
	return (textures.count(id) > 0) ? textures[id] : nullptr;
}

void AssetManager::loadTexture(std::string id, std::string path) {
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


sf::Image* AssetManager::getImage(std::string id) {
	return (images.count(id) > 0) ? images[id] : nullptr;
}

void AssetManager::loadImage(std::string id, std::string path) {
	if (images.count(id) <= 0)
	{
		sf::Image* image = new sf::Image();
		if (!image->loadFromFile(path.c_str()))
		{
			std::cout << "Failed to load Image : [" << path << "]" << std::endl;
			return;
		}
		else
		{
			images[id] = image;
			std::cout << "Image: [" << path << "] loaded !" << std::endl;
		}

	}
}


sf::Font* AssetManager::getFont(std::string id) {
	return (fonts.count(id) > 0) ? fonts[id] : nullptr;
}

void AssetManager::loadFont(std::string id, std::string path) {
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

sf::Music* AssetManager::getMusic(std::string id) {
	return (musics.count(id) > 0) ? musics[id] : nullptr;
}

void AssetManager::loadMusic(std::string id, std::string path) {
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

void AssetManager::playMusic(std::string id, bool loop) {
    if (musics.count(id) > 0) {
        musics[id]->setLoop(loop);
        if (m_isMusicMuted)
            musics[id]->setVolume(0);
        else
            musics[id]->setVolume(m_musicVolume*10);
        musics[id]->play();
    }
}

void AssetManager::setSoundVolume(unsigned int volume) {
    m_musicVolume = volume;
    applyMusicVolume();
}

unsigned int AssetManager::getSoundVolume() const {
    return m_musicVolume;
}


bool AssetManager::isMusicMuted() const {
	return m_isMusicMuted;
}

void AssetManager::muteMusic() {
	m_isMusicMuted = !m_isMusicMuted;
    applyMusicVolume();
}

void AssetManager::muteMusic(bool mute) {
	m_isMusicMuted = mute;
    applyMusicVolume();
}





void AssetManager::clean() {

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

void AssetManager::applyMusicVolume() {
    for (auto it = musics.begin(); it != musics.end(); it++)
    {
        if (m_isMusicMuted)
        {
            it->second->setVolume(0);
        }
        else
        {
            it->second->setVolume(m_musicVolume * 10);
        }
    }
}



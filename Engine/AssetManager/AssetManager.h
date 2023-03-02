#pragma once

#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class AssetManager
{
public:
	void clean();

	sf::Texture* getTexture(std::string id);
	void loadTexture(std::string id, std::string path);

	sf::Font* getFont(std::string id);
	void loadFont(std::string id, std::string path);

	sf::Music* getMusic(std::string id);
	void loadMusic(std::string id, std::string path, int volume);

	inline static AssetManager& get() {
		if (s_instance == nullptr) {
			s_instance = new AssetManager();
		}
		return *s_instance;
	}
	
private:
	static AssetManager* s_instance;
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Music*> musics;
protected:
	AssetManager();
	~AssetManager() = default;

};
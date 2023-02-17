#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class AssetManagerTemp
{
public:
	AssetManagerTemp();
	~AssetManagerTemp() = default;

	void clean();

	sf::Texture* getTexture(std::string id);
	void loadTexture(std::string id, std::string path);

	sf::Font* getFont(std::string id);
	void loadFont(std::string id, std::string path, int fontSize);

	sf::Music* getMusic(std::string id);
	void loadMusic(std::string id, std::string path, int volume);

	inline static AssetManagerTemp& get() {
		if (s_instance == nullptr) {
			s_instance = new AssetManagerTemp();
		}
		return *s_instance;
	}
	
private:
	static AssetManagerTemp* s_instance;
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Music*> musics;
};
#include <mutex>
#include "SFML/Graphics.hpp"

class UI
{
public:
	UI() = default;
	~UI() = default;
	void CreateText(std::string name, sf::Color colorText, std::string text, int characterSize, sf::Vector2f position, sf::Font& font);
	sf::Text& Text(const std::string& name);
    void UpdateText(std::string name, std::string text);
	sf::RectangleShape& Zone(const std::string& name);
	bool InteractionButton(std::string name, sf::Vector2i mouseposition);
    void RemoveText(std::string name);

private:

	std::mutex _mutex;

	std::vector<sf::String> nameButton;
	std::vector<sf::Text> listButtons;

	sf::Text buttonModel;

	std::vector<sf::String> nameTextBox;
	std::vector<sf::RectangleShape> zone;
};
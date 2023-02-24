#include <mutex>
#include "SFML/Graphics.hpp"
#include <iostream>

#ifndef UI_H
#define UI_H

class UI
{
public:
	UI()
	{
		if (!font.loadFromFile("../../../../assets/font/shanghai.ttf"))
		{
			std::cout << "Failed to load font" << std::endl;
			return;
		}
	}

	~UI() = default;
	void CreateText(std::string name, sf::Color colorText, std::string text, int characterSize, sf::Vector2f position, sf::Font& font);
	sf::Text& Text(const std::string& name);
	sf::RectangleShape& Zone(const std::string& name);
	bool InteractionButton(std::string name, sf::Vector2i mouseposition);

	sf::Font& getFont();

private:

	std::mutex _mutex;

	std::vector<sf::String> nameButton;
	std::vector<sf::Text> listButtons;

	sf::Text buttonModel;

	sf::Font font;

	std::vector<sf::String> nameTextBox;
	std::vector<sf::RectangleShape> zone;
};

#endif // UI_H
#pragma once

#include <mutex>
#include "SFML/Graphics.hpp"
#include <iostream>

enum EShape
{
    Rectangle=1,
};

/*
enum EOrigin
{
    Center=1,
    TopLeft=2,
    TopRight=3,
    BottomLeft=4,
    BottomRight=5,
    MiddleLeft=6,
    MiddleRight=7,
};
*/

class UI
{
public:
	UI() = default;
	~UI(){
        listButtons.clear();
        nameButton.clear();
        zone.clear();
    };
	void CreateText(std::string name, sf::Color colorText, std::string text, int characterSize, sf::Vector2f position, sf::Font& font);
//    void CreateText(std::string name, sf::Color colorText, std::string text, int characterSize, sf::Vector2f position, sf::Font& font, EOrigin origin);
    sf::Text& Text(const std::string& name);
    sf::Text& Text(int i);
    int TextExist(std::string name);
    void UpdateText(std::string name, std::string text);
    void CreateShape(std::string name, EShape shape, sf::Vector2f position, sf::Vector2f size, sf::Color color);
    void CreateZone(std::string name, sf::Vector2f position, sf::Vector2f size, sf::Color color);
    int ZoneExist(std::string name);
    sf::RectangleShape& Zone(const std::string& name);
	bool InteractionButton(std::string name, sf::Vector2i mouseposition);
    void RemoveText(std::string name);
    void RemoveZone(std::string name);
//    void setOrigin(sf::Text text, EOrigin origin);

//	sf::Font& getFont();

    void AddTextToZone(std::string TextName, std::string ZoneName);

private:

	std::mutex _mutex;

	std::vector<sf::String> nameButton;
	std::vector<sf::Text> listButtons;

	sf::Text buttonModel;

	std::map<std::string, sf::RectangleShape> zone;

};

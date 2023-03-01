#include "UI.hpp"
#include <iostream>


void UI::CreateText(std::string name, sf::Color colorText, std::string text, int characterSize, sf::Vector2f position, sf::Font& font)
{
	buttonModel.setFont(font);
	buttonModel.setFillColor(colorText);
	buttonModel.setString(text);
	buttonModel.setCharacterSize(characterSize);
	buttonModel.setOrigin(buttonModel.getGlobalBounds().width / 2, buttonModel.getGlobalBounds().height / 2);
	buttonModel.setPosition(position);

	listButtons.push_back(buttonModel);
	nameButton.emplace_back(name);
}

sf::Text& UI::Text(const std::string& name)
{
	std::lock_guard guard(_mutex);

    int i = TextExist(name);
    if (i > -1)
    {
        return listButtons.at(i);
    }
    else
    {
        std::cout << "Error: Text not found" << std::endl;
    }

	for (int i = 0; i < nameButton.size(); i++)
	{
		if (nameButton[i] == name)
		{
			return listButtons.at(i);
		}
	}
}
sf::Text& UI::Text(int i)
{
    return listButtons.at(i);
}


int UI::TextExist(std::string name)
{
    for (int i = 0; i < nameButton.size(); i++)
    {
        if (nameButton[i] == name)
        {
            return i;
        }
    }
    return -1;
}

sf::RectangleShape& UI::Zone(const std::string& name)
{
	for (int i = 0; i < nameTextBox.size(); i++)
	{
		if (nameTextBox[i] == name)
		{
			return zone.at(i);
		}
	}
}

bool UI::InteractionButton(std::string name, sf::Vector2i mouseposition)
{
    int i = TextExist(name);
    if(i == -1)
    {
        std::cout << "Error: Text not found" << std::endl;
        return false;
    }
	if (Text(i).getGlobalBounds().contains(mouseposition.x, mouseposition.y))
	{
		Text(i).setColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << name << " activated" << std::endl;
			return true;
		}
		else return false;
	}
	else
	{
		Text(i).setColor(sf::Color::White);
		return false;
	}

}

void UI::RemoveText(std::string name) {
    for (int i = 0; i < nameButton.size(); i++)
    {
        if (nameButton[i] == name)
        {
            listButtons.erase(listButtons.begin() + i);
            nameButton.erase(nameButton.begin() + i);
        }
    }

}

void UI::UpdateText(std::string name, std::string text) {
    for (int i = 0; i < nameButton.size(); i++)
    {
        if (nameButton[i] == name)
        {
            listButtons[i].setString(text);
        }
    }
}

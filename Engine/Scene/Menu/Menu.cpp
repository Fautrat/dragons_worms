#include "Menu.hpp"


Menu::Menu(std::string name) {
    _Name = name;
    _Elements.reserve(10);
    _State = EStateMenu::Active;
}


void Menu::AddButton(std::string buttonName, std::function<void(void)> callback) {
        std::unique_ptr<UiElement> element = std::make_unique<UiElement>(EElementType::Button, buttonName, callback);
        _Elements.push_back(std::move(element));
}

//void Menu::AddButton(std::vector<std::string> buttonNames) {
//    for (auto buttonName : buttonNames) {
//        std::unique_ptr<UiElement> element = std::make_unique<UiElement>(EElementType::Button, buttonName);
//        _Elements.push_back(std::move(element));
//    }
//}

void Menu::RemoveButton(std::string buttonName) {
    for (auto it = _Elements.begin(); it != _Elements.end(); ++it) {
        if ((*it)->Name == buttonName) {
            _Elements.erase(it);
            break;
        }
    }
}


std::vector<std::string> Menu::GetButtons() const {
    std::vector<std::string> _Buttons;
    for (int i = 0; i < _Elements.size(); i++) {
        if (_Elements[i]->Type == EElementType::Button) {
            _Buttons.push_back(_Elements[i]->Name);
        }
    }
    return _Buttons;
}

void Menu::AddZone(std::string shapeName, std::function<void(void)> callback) {
    std::unique_ptr<UiElement> element = std::make_unique<UiElement>(EElementType::Zone, shapeName, callback);
    _Elements.push_back(std::move(element));
}

void Menu::RemoveZone(std::string shapeName) {
    for (auto it = _Elements.begin(); it != _Elements.end(); ++it) {
        if ((*it)->Name == shapeName) {
            _Elements.erase(it);
            break;
        }
    }
}

std::string const Menu::GetName() const {
    return _Name;
}

std::vector<std::unique_ptr<UiElement>> &Menu::GetElements()  {
    return _Elements;
}

void Menu::SetState(EStateMenu state) {
    _State = state;
}

EStateMenu Menu::GetState() const {
    return _State;
}


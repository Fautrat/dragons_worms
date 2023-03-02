#pragma once
#include <string>
#include <vector>

enum EElementType {
    Button = 1,
    Text,
    Zone,
};

struct UiElement {
    EElementType Type;
    std::string Name;

    UiElement() = default;
    UiElement(EElementType type, std::string name): Type(type), Name(name){};
};

class Menu {
public:
    Menu(std::string name): _Name(name){};
    virtual ~Menu(){
        _Elements.clear();
    };

    void AddButton(std::string buttonName){
        std::unique_ptr<UiElement> element = std::make_unique<UiElement>(EElementType::Button, buttonName);
        _Elements.push_back(std::move(element));
    };

    void AddButton(std::vector<std::string> buttonNames){
        for (auto buttonName : buttonNames) {
            std::unique_ptr<UiElement> element = std::make_unique<UiElement>(EElementType::Button, buttonName);
            _Elements.push_back(std::move(element));
        }
    };

    void AddZone(std::string shapeName){
        std::unique_ptr<UiElement> element = std::make_unique<UiElement>(EElementType::Zone, shapeName);
        _Elements.push_back(std::move(element));
    };

    std::string GetName() {
        return _Name;
    }

    std::vector<std::string> GetButtons(){
        std::vector<std::string> _Buttons;
        for (int i = 0; i < _Elements.size(); i++) {
            if (_Elements[i]->Type == EElementType::Button) {
                _Buttons.push_back(_Elements[i]->Name);
            }
        }
        return _Buttons;
    }

    std::vector<std::unique_ptr<UiElement>>& GetElements() {
        return _Elements;
    }



private:

//    std::vector<std::string> _Buttons;
    std::vector<std::unique_ptr<UiElement>> _Elements;
    std::string _Name;
};


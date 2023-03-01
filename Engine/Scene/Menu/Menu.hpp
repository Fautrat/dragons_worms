#pragma once
#include <string>
#include <vector>

class Menu {
public:
    Menu(std::string name): _Name(name){};
    virtual ~Menu(){
        _Buttons.clear();
    };

    void AddButton(std::string buttonName){
        _Buttons.push_back(buttonName);
    };

    void AddButton(std::vector<std::string> buttonNames){
        for (auto buttonName : buttonNames) {
            _Buttons.push_back(buttonName);
        }
    };

    std::string GetName() {
        return _Name;
    }

    std::vector<std::string> GetButtons(){
        return _Buttons;
    }



private:
    std::vector<std::string> _Buttons;
    std::string _Name;
};


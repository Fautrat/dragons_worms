#pragma once
#include "Menu.hpp"
#include <map>

class MenuManager{
public:
    MenuManager() {
        _CurrentMenu = nullptr;
        _Menus = std::vector<std::shared_ptr<Menu>>();
    }
    virtual ~MenuManager(){
        RemoveAllMenu();
    };
    void AddMenu(std::shared_ptr<Menu> menu){
        _Menus.emplace_back(std::move(menu));
    };
    void RemoveMenu(std::string menuName){
        for (auto it = _Menus.begin(); it != _Menus.end(); ++it) {
            if ((*it)->GetName() == menuName) {
                _Menus.erase(it);
                break;
            }
        }
    };

    std::shared_ptr<Menu> GetMenu(std::string menuName){
        for (auto it = _Menus.begin(); it != _Menus.end(); ++it) {
            if ((*it)->GetName() == menuName) {
                return (*it);
            }
        }
        return nullptr;
    }

//    void RemoveMenuAndButtons(std::string menuName, UI *ui) {
//        for (auto it = _Menus.begin(); it != _Menus.end(); ++it) {
//            if ((*it)->GetName() == menuName) {
//                for (auto button : (*it)->GetButtons()) {
//                    ui->RemoveText(button);
//                }
//                _Menus.erase(it);
//                break;
//            }
//        }
//    }


    void RemoveAllMenu(){
        _Menus.clear();
    };
    void SetCurrentMenu(std::string menuName){
        for (auto it = _Menus.begin(); it != _Menus.end(); ++it) {
            if ((*it)->GetName() == menuName) {
                _CurrentMenu = (*it);
            }
        }
    };
    std::shared_ptr<Menu> GetCurrentMenu(){
        return _CurrentMenu;
    };
private:
    std::vector<std::shared_ptr<Menu>> _Menus = std::vector<std::shared_ptr<Menu>>();
    std::shared_ptr<Menu> _CurrentMenu;
};

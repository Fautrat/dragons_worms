#pragma once
#include "Menu.hpp"
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <functional>
#include <utility>


class UI;

class MenuManager{
public:
    MenuManager(sf::Font &font);
    explicit MenuManager(std::shared_ptr<UI> ui, sf::Font& font) : _ui(std::move(ui)), _font(font) {
        _CurrentMenu = nullptr;
        _Menus = std::vector<std::shared_ptr<Menu>>();
    };
    virtual ~MenuManager();

    void SetFont(sf::Font& font);

    void AddMenu(std::shared_ptr<Menu> menu);
    void RemoveMenu(std::string menuName);
    void ApplyRemoveMenu(std::string menuName);
    void CheckEachMenuState();

    void AddText(std::string name, sf::Color colorText, std::string text, int characterSize, sf::Vector2f position, std::function<void(void)> callback);
    void UpdateText(std::string name, std::string text);
    void RemoveText(std::string name);

    void AddZone(std::string name, sf::Vector2f position, sf::Vector2f size, sf::Color color, std::function<void(void)> callback);
    void RemoveZone(std::string name);

    std::shared_ptr<Menu> GetMenu(std::string menuName);

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

    void RemoveAllMenu();
    void SetCurrentMenu(std::string menuName);
    std::shared_ptr<Menu> GetCurrentMenu() const;

    void Render(sf::RenderTarget* renderTarget);
    void Update(const float& deltaTime, sf::Vector2i mousepos);

private:
    std::vector<std::shared_ptr<Menu>> _Menus = std::vector<std::shared_ptr<Menu>>();
    std::shared_ptr<Menu> _CurrentMenu;
    std::shared_ptr<UI> _ui;
    sf::Font& _font;
};

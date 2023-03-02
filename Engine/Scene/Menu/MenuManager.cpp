#include "MenuManager.hpp"
#include "../../UI/UI.hpp"


MenuManager::MenuManager(sf::Font &font) : _font(font) {
    _CurrentMenu = nullptr;
    _Menus = std::vector<std::shared_ptr<Menu>>();
    _ui = nullptr;
}

MenuManager::MenuManager(std::shared_ptr<UI> ui, sf::Font &font) : _ui(std::move(ui)), _font(font) {
    _CurrentMenu = nullptr;
    _Menus = std::vector<std::shared_ptr<Menu>>();
}

MenuManager::~MenuManager() {
    RemoveAllMenu();

}

void MenuManager::AddMenu(std::shared_ptr<Menu> menu) {
    if(GetMenu(menu->GetName()) != nullptr)
    {
        return;
    }
    _Menus.emplace_back(std::move(menu));
}

void MenuManager::RemoveMenu(std::string menuName) {
    GetMenu(menuName)->SetState(EStateMenu::ToDelete);
}

void MenuManager::ApplyRemoveMenu(std::string menuName) {
    for (auto& button : GetMenu(menuName)->GetButtons())
    {
        RemoveText(button);
    }
    for (auto it = _Menus.begin(); it != _Menus.end(); ++it) {
        if ((*it)->GetName() == menuName) {
            _Menus.erase(it);
            break;
        }
    }
}

void MenuManager::CheckEachMenuState(){
    for (auto& menu : _Menus)
    {
        if (menu->GetState() == EStateMenu::ToDelete)
        {
            ApplyRemoveMenu(menu->GetName());
        }
    }
}

void MenuManager::AddText(std::string name, sf::Color colorText, std::string text, int characterSize,
                                sf::Vector2f position, std::function<void(void)> callback) {
    _ui->CreateText(name, colorText, text, characterSize, position, _font);
    _CurrentMenu->AddButton(name, callback);
}


std::shared_ptr<Menu> MenuManager::GetMenu(std::string menuName) {
    for (auto it = _Menus.begin(); it != _Menus.end(); ++it) {
        if ((*it)->GetName() == menuName) {
            return (*it);
        }
    }
    return nullptr;
}

void MenuManager::RemoveAllMenu() {
    _Menus.clear();
};

void MenuManager::SetCurrentMenu(std::string menuName) {
    for (auto it = _Menus.begin(); it != _Menus.end(); ++it) {
        if ((*it)->GetName() == menuName) {
            _CurrentMenu = (*it);
        }
    }
}

std::shared_ptr<Menu> MenuManager::GetCurrentMenu() const {
    return _CurrentMenu;
}

void MenuManager::RemoveText(std::string name) {
    _ui->RemoveText(name);
    _CurrentMenu->RemoveButton(name);

}

void MenuManager::AddZone(std::string name, sf::Vector2f position, sf::Vector2f size, sf::Color color, std::function<void(void)> callback) {
    _ui->CreateZone(name, position, size, color);
    _CurrentMenu->AddZone(name, callback);
}

void MenuManager::RemoveZone(std::string name) {
    _ui->RemoveZone(name);
    _CurrentMenu->RemoveZone(name);

}

void MenuManager::UpdateText(std::string name, std::string text) {
    _ui->UpdateText(name, text);

}

void MenuManager::Render(sf::RenderTarget* renderTarget) {
    if (GetCurrentMenu()->GetState() == EStateMenu::Hidden) return;
    for(auto& element : GetCurrentMenu()->GetElements())
    {
        if (element->Type == EElementType::Button) {
            int i = _ui->TextExist(element->Name);
            if (i > -1) renderTarget->draw(_ui->Text(i));
        }
        else if (element->Type == EElementType::Text) {
            int i = _ui->TextExist(element->Name);
            if (i > -1) renderTarget->draw(_ui->Text(i));
        }
        else if(element->Type == EElementType::Zone)
        {
            int i = _ui->ZoneExist(element->Name);
            renderTarget->draw(_ui->Zone(element->Name));
        }
    }

}

void MenuManager::Update(const float &deltaTime, sf::Vector2i mousepos) {
    CheckEachMenuState();
    std::string name =  GetCurrentMenu()->GetName();
    for(auto& element : GetCurrentMenu()->GetElements())
    {
        if (element->Type == EElementType::Button) {
            if (_ui->InteractionButton(element->Name, mousepos)) {
                element->Callback();
            }
        }
        else if (element->Type == EElementType::Zone)
        {
            if (_ui->InteractionButton(element->Name, mousepos)) {
                element->Callback();
            }
        }
    }
}

void MenuManager::SetFont(sf::Font &font) {
    _font = font;
}

void MenuManager::AddTextToZone(std::string TextName, std::string ZoneName) {
//    _ui->AddTextToZone(TextName, ZoneName);
    _ui->Text(TextName).setOrigin(_ui->Zone(ZoneName).getOrigin());

}

void MenuManager::SetTextOrigin(std::string name, sf::Vector2f origin) {
    _ui->Text(name).setOrigin(origin);
}

void MenuManager::SetZoneOrigin(std::string name, sf::Vector2f origin) {
    _ui->Zone(name).setOrigin(origin);
}

void MenuManager::SetZonePosition(std::string name, sf::Vector2f position) {
    _ui->Zone(name).setPosition(position);
}


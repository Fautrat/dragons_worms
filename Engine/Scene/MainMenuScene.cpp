#include "MainMenuScene.hpp"
#include <iostream>


void resizeButton( std::shared_ptr<UI> ui, std::string buttonName, float x, float y)
{
    ui->Text(buttonName).setOrigin(0, ui->Text(buttonName).getGlobalBounds().height / 2);
    ui->Text(buttonName).setPosition(x - ui->Text(buttonName).getGlobalBounds().width / 2, y);
}

std::vector<float> getArrayOfFloatFromWidth(int width, int size)
{
    std::vector<float> array;
    float x = 0;
    for (int i = 0; i < size; i++)
    {
        x += width / size+1;
        array.push_back(x);
    }
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << std::endl;
    }
    return array;
}


MainMenuScene::MainMenuScene(Engine& engine) :Scene(engine)
{
    AssetManager::get().loadFont("Shangai", "assets/font/shanghai.ttf");

    ui = std::make_shared<UI>();
    m_input = &engine.getInputHandler();
    if (!videoTexture.loadFromFile("assets/Maps/wallpaper.jpg"))
    {
        std::cout << "Failed to load video" << std::endl;
        return;
    }
 
    menuManager = new MenuManager(ui, *AssetManager::get().getFont("Shangai"));

    AssetManager::get().loadMusic("music", "assets/sound/Dragon.ogg");

    videoSprite.setTexture(videoTexture);

    videoSprite.setScale({ (float)1920 / (float)videoSprite.getTexture()->getSize().x, (float)1080 / (float)videoSprite.getTexture()->getSize().y });

    std::shared_ptr<Menu> mainMenu = std::make_shared<Menu>("MainMenu");
    menuManager->AddMenu(mainMenu);
    menuManager->SetCurrentMenu("MainMenu");

    menuManager->AddText("PlayButton", sf::Color::White, "PLAY", 300, sf::Vector2f(400, 200), [&] {Play(); });
    menuManager->AddText("OptionsButton", sf::Color::White, "OPTIONS", 200, sf::Vector2f(400, 525), [&] {Options(); });
    menuManager->AddText("QuitButton", sf::Color::White, "QUIT", 200, sf::Vector2f(400, 800), [&] {Quit(); });

}

MainMenuScene::~MainMenuScene()
{
//    delete music;
//    music = nullptr;
    // delete shared pointer
    ui.reset();
    delete menuManager;
    menuManager = nullptr;
}

void MainMenuScene::Start()
{
    AssetManager::get().setSoundVolume(2);
    AssetManager::get().playMusic("music");
}

void MainMenuScene::Update(const float& deltaTime)
{
    if(m_isclicked)
    {
        delay += deltaTime;
        if(delay >= 0.2f)
        {
            m_isclicked = false;
            delay = 0.0f;
        }
    }
    else
    {
        sf::Vector2i mousepos = engine->getMousePos();
        if (menuManager->GetCurrentMenu()->GetName() == "Controls")
        {
            if (m_is_remap){
                // if not clicked or esc or enter
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) CancelRemap();
                else Remap();
            }
            if (ui->InteractionButton("MOVEUP", mousepos)) UpdateInput(EInput::MoveUp, "MOVEUP");
            if (ui->InteractionButton("MOVEDOWN", mousepos)) UpdateInput(EInput::MoveDown, "MOVEDOWN");
            if (ui->InteractionButton("MOVELEFT", mousepos)) UpdateInput(EInput::MoveLeft, "MOVELEFT");
            if (ui->InteractionButton("MOVERIGHT", mousepos)) UpdateInput(EInput::MoveRight, "MOVERIGHT");
            if (ui->InteractionButton("ACTION", mousepos)) UpdateInput(EInput::Action, "ACTION");
            if (ui->InteractionButton("JUMP", mousepos)) UpdateInput(EInput::Jump, "JUMP");
            if (ui->InteractionButton("SELECTWEAPON1", mousepos)) UpdateInput(EInput::SelectWeapon1, "SELECTWEAPON1");
            if (ui->InteractionButton("SELECTWEAPON2", mousepos)) UpdateInput(EInput::SelectWeapon2, "SELECTWEAPON2");
            if (ui->InteractionButton("BackControlsButton", mousepos)) Back();
        }
        else menuManager->Update(deltaTime, mousepos);
    }
}



void MainMenuScene::Render(sf::RenderTarget* renderTarget)
{
    renderTarget->draw(videoSprite);
    menuManager->Render(renderTarget);
}

void MainMenuScene::Play()
{
    m_isclicked = false;
    engine->setSceneToLoad(MAINGAME);
}

void MainMenuScene::Quit()
{
    m_isclicked = false;
    engine->ExitGame();
}

void MainMenuScene::Options()
{
    std::cout << "Options pressed" << std::endl;

    std::shared_ptr<Menu> optionsMenu = std::make_shared<Menu>("Options");

    menuManager->AddMenu(optionsMenu);
    menuManager->SetCurrentMenu("Options");

    // get resolution
    sf::Vector2<int> res = engine->getResolution();
    int backSize = 150,
        controlsSize = 100,
        volumeSize = 100;


    float   BackOptionsButton_y = ((float)res.y / 4.f) - ((float)backSize / 2.f),
            ControlsButton_y    = ((float)res.y - BackOptionsButton_y) / 3.f - ((float)controlsSize / 2.f),
            VolumeButton_y      = ((float)res.y - BackOptionsButton_y) / 3.f * 2.f - ((float)volumeSize / 2.f);

    BackOptionsButton_y = ((float)res.y / 4.f * 3.f) - ((float)backSize / 2.f);


    menuManager->AddText("BackOptionsButton", sf::Color::White, "BACK", backSize, sf::Vector2f(400, BackOptionsButton_y), [&]{ Back(); });
//    menuManager->AddText("ResolutionButton", sf::Color::White, "RESOLUTION", 100, sf::Vector2f(400, 525), [&]{ Resolution(); });
    menuManager->AddText("ControlsButton", sf::Color::White, "CONTROLS", controlsSize, sf::Vector2f(400, ControlsButton_y), [&]{ Controls(); });
    menuManager->AddText("VolumeButton", sf::Color::White, "VOLUME", volumeSize, sf::Vector2f(400, VolumeButton_y), [&]{ Volume(); });

    m_isclicked = true;
}

void MainMenuScene::Controls()
{
    std::cout << "Controls pressed" << std::endl;
    m_isclicked = true;
    std::shared_ptr<Menu> controlsMenu = std::make_shared<Menu>("Controls");
    menuManager->AddMenu(controlsMenu);
    menuManager->SetCurrentMenu("Controls");

    sf::Vector2<int> res = engine->getResolution();

    float MoveUp_y = (float)res.y / 10 * 1,
          MoveDown_y = (float)res.y / 10 * 2,
          MoveLeft_y = (float)res.y / 10 * 3,
          MoveRight_y = (float)res.y / 10 * 4,
          Action_y = (float)res.y / 10 * 5,
          Jump_y = (float)res.y / 10 * 6,
          Select1_y = (float)res.y / 10 * 7,
          Select2_y = (float)res.y / 10 * 8,
          back_y = (float)res.y / 5.f * 4.5f;


    menuManager->AddText("MOVEUP", sf::Color::White, "UP : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveUp)), 100, sf::Vector2f(400, 300), [&]{ UpdateInput(EInput::MoveUp, "MOVEUP"); });
    resizeButton(ui, "MOVEUP", 400, MoveUp_y);
    menuManager->AddText("MOVEDOWN", sf::Color::White, "DOWN : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveDown)), 100, sf::Vector2f(400, 400), [&]{ UpdateInput(EInput::MoveDown, "MOVEDOWN"); });
    resizeButton(ui, "MOVEDOWN", 400, MoveDown_y);
    menuManager->AddText("MOVELEFT", sf::Color::White, "LEFT : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveLeft)), 100, sf::Vector2f(400, 500), [&]{ UpdateInput(EInput::MoveLeft, "MOVELEFT"); });
    resizeButton(ui, "MOVELEFT", 400, MoveLeft_y);
    menuManager->AddText("MOVERIGHT", sf::Color::White, "RIGHT : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveRight)), 100, sf::Vector2f(400, 600), [&]{ UpdateInput(EInput::MoveRight, "MOVERIGHT"); });
    resizeButton(ui, "MOVERIGHT", 400, MoveRight_y);
    menuManager->AddText("ACTION", sf::Color::White, "ACTION : " + m_input->fromKtoS(m_input->getActionKey(EInput::Action)), 100, sf::Vector2f(400, 700), [&]{ UpdateInput(EInput::Action, "ACTION"); });
    resizeButton(ui, "ACTION", 400, Action_y);
    menuManager->AddText("JUMP", sf::Color::White, "JUMP : " + m_input->fromKtoS(m_input->getActionKey(EInput::Jump)), 100, sf::Vector2f(400, 800), [&]{ UpdateInput(EInput::Jump, "JUMP"); });
    resizeButton(ui, "JUMP", 400, Jump_y);
    menuManager->AddText("SELECTWEAPON1", sf::Color::White, "WEAPON 1 : " + m_input->fromKtoS(m_input->getActionKey(EInput::SelectWeapon1)), 100, sf::Vector2f(400, 800), [&] { UpdateInput(EInput::SelectWeapon1, "SELECTWEAPON1"); });
    resizeButton(ui, "SELECTWEAPON1", 400, Select1_y);
    menuManager->AddText("SELECTWEAPON2", sf::Color::White, "WEAPON 2 : " + m_input->fromKtoS(m_input->getActionKey(EInput::SelectWeapon2)), 100, sf::Vector2f(400, 800), [&] { UpdateInput(EInput::SelectWeapon2, "SELECTWEAPON2"); });
    resizeButton(ui, "SELECTWEAPON2", 400, Select2_y);
    menuManager->AddText("BackControlsButton", sf::Color::White, "BACK", 150, sf::Vector2f(400, 900), [&]{ Back(); });
    resizeButton(ui, "BackControlsButton", 400, back_y);
}



void MainMenuScene::UpdateInput(EInput action, std::string buttonName)
{
    std::cout << "UpdateInput" << std::endl;
    std::string text = buttonName + " : ";
    // orange
    sf::Color orangeColor = sf::Color(169, 134, 104);

    menuManager->AddZone("UpdateZone", sf::Vector2f(400, 400), sf::Vector2f(400, 400), orangeColor, [&]{} );
    menuManager->AddText("UpdateText", sf::Color::White, "Update", 100, sf::Vector2f(400, 400), [&]{});

    m_isclicked = true;
    m_is_remap = true;
    m_actionToRemap = action;
}



void MainMenuScene::Remap() {
    for (sf::Keyboard::Key key = sf::Keyboard::A; key <= sf::Keyboard::KeyCount; key = sf::Keyboard::Key(key + 1)) {
        if (sf::Keyboard::isKeyPressed(key)) {
            m_is_remap = false;
            m_isclicked = false;
            std::cout << "Remap : " << m_input->fromKtoS(key) << std::endl;
            m_input->remapAction(m_actionToRemap, key);
            sf::Vector2<int> res = engine->getResolution();
            float MoveUp_y = (float)res.y / 10 * 1,
                MoveDown_y = (float)res.y / 10 * 2,
                MoveLeft_y = (float)res.y / 10 * 3,
                MoveRight_y = (float)res.y / 10 * 4,
                Action_y = (float)res.y / 10 * 5,
                Jump_y = (float)res.y / 10 * 6,
                Select1_y = (float)res.y / 10 * 7,
                Select2_y = (float)res.y / 10 * 8;

            switch (m_actionToRemap) {
                case EInput::MoveUp:
                    menuManager->UpdateText("MOVEUP", "UP : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveUp)));
                    resizeButton(ui, "MOVEUP", 400, MoveUp_y);
                    break;
                case EInput::MoveDown:
                    menuManager->UpdateText("MOVEDOWN", "DOWN : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveDown)));
                    resizeButton(ui, "MOVEDOWN", 400, MoveDown_y);
                    break;
                case EInput::MoveLeft:
                    menuManager->UpdateText("MOVELEFT", "LEFT : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveLeft)));
                    resizeButton(ui, "MOVELEFT", 400, MoveLeft_y);
                    break;
                case EInput::MoveRight:
                    menuManager->UpdateText("MOVERIGHT", "RIGHT : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveRight)));
                    resizeButton(ui, "MOVERIGHT", 400, MoveRight_y);
                    break;
                case EInput::Action:
                    menuManager->UpdateText("ACTION", "ACTION : " + m_input->fromKtoS(m_input->getActionKey(EInput::Action)));
                    resizeButton(ui, "ACTION", 400, Action_y);
                    break;
                case EInput::Jump:
                    menuManager->UpdateText("JUMP", "JUMP : " + m_input->fromKtoS(m_input->getActionKey(EInput::Jump)));
                    resizeButton(ui, "JUMP", 400, Jump_y);
                    break;
                case EInput::SelectWeapon1:
                    menuManager->UpdateText("SELECTWEAPON1", "WEAPON 2 : " + m_input->fromKtoS(m_input->getActionKey(EInput::SelectWeapon1)));
                    resizeButton(ui, "SELECTWEAPON1", 400, Select1_y);
                    break;
                case EInput::SelectWeapon2:
                    menuManager->UpdateText("SELECTWEAPON2", "WEAPON 2 : " + m_input->fromKtoS(m_input->getActionKey(EInput::SelectWeapon2)));
                    resizeButton(ui, "SELECTWEAPON2", 400, Select2_y);
                    break;
                default:
                    break;
            }

            menuManager->RemoveText("UpdateText");
            menuManager->RemoveZone("UpdateZone");
            break;
        }
    }
}

void MainMenuScene::CancelRemap() {
    m_is_remap = false;
    m_isclicked = false;
    menuManager->RemoveText("UpdateText");
    menuManager->RemoveZone("UpdateZone");
}


void MainMenuScene::Resolution()
{
    std::cout << "Resolution pressed" << std::endl;
    m_isclicked = true;

    std::shared_ptr<Menu> resolutionMenu = std::make_shared<Menu>("Resolution");
    menuManager->AddMenu(resolutionMenu);
    menuManager->SetCurrentMenu("Resolution");

    menuManager->AddText("2560x1600", sf::Color::White, "2560x1600", 100, sf::Vector2f(400, 750), [&]{ SetResolution(2560, 1600); });
    menuManager->AddText("1920x1080", sf::Color::White, "1920x1080", 100, sf::Vector2f(400, 525), [&]{ SetResolution(1920, 1080); });
    menuManager->AddText("1280x720", sf::Color::White, "1280x720", 100, sf::Vector2f(400, 300), [&]{ SetResolution(1280, 720); });
    menuManager->AddText("BackResolutionButton", sf::Color::White, "BACK", 200, sf::Vector2f(400, 900), [&]{ Back(); });

}

void MainMenuScene::SetResolution(int width, int height)
{
    engine->getRenderWindow().setSize(sf::Vector2u(width, height));
//    videoSprite.setScale({ (float)width / (float)videoSprite.getTexture()->getSize().x, (float)height / (float)videoSprite.getTexture()->getSize().y });
//    videoSprite.setPosition(0, 0);
}

void MainMenuScene::Volume() {
    std::cout << "Volume pressed" << std::endl;
    m_isclicked = true;

    std::shared_ptr<Menu> volumeMenu = std::make_shared<Menu>("Volume");
//    volumeMenu->AddButton("BackVolumeButton", [&]{ Back(); });
    menuManager->AddMenu(volumeMenu);
    menuManager->SetCurrentMenu("Volume");

    sf::Vector2<int> res = engine->getResolution();

    float volume_y = (float)res.y / 5.f * 1.f,
        mute_y = (float)res.y / 5.f * 2.5f,
        back_y = (float)res.y / 5.f * 4.f;

    menuManager->AddText("ReduceVolume", sf::Color::White, "<-", 100, sf::Vector2f(100, volume_y), [&]{ ReduceVolume(); });
    menuManager->AddText("Volume", sf::Color::White, "VOLUME : " + std::to_string(AssetManager::get().getSoundVolume()), 100, sf::Vector2f(450, volume_y), [&]{ });
    menuManager->AddText("IncreaseVolume", sf::Color::White, "->", 100, sf::Vector2f(750, volume_y), [&]{ IncreaseVolume(); });
    std::string mute = AssetManager::get().isMusicMuted() ? "true" : "false";
    menuManager->AddText("Mute", sf::Color::White, "MUTE : " + mute, 100, sf::Vector2f(400, mute_y), [&]{ Mute(); });
    menuManager->AddText("BackVolumeButton", sf::Color::White, "BACK", 150, sf::Vector2f(400, back_y), [&]{ Back(); });

}

void MainMenuScene::ReduceVolume() {
    if (AssetManager::get().getSoundVolume() > 0) {
        AssetManager::get().setSoundVolume(AssetManager::get().getSoundVolume() - 1);
        menuManager->UpdateText("Volume", "VOLUME : " + std::to_string(AssetManager::get().getSoundVolume()));
    }
    m_isclicked = true;
}

void MainMenuScene::IncreaseVolume() {
    if (AssetManager::get().getSoundVolume() < 10) {
        AssetManager::get().setSoundVolume(AssetManager::get().getSoundVolume() + 1);
        menuManager->UpdateText("Volume", "VOLUME : " + std::to_string(AssetManager::get().getSoundVolume()));
    }
    m_isclicked = true;
}

void MainMenuScene::Mute() {
    AssetManager::get().muteMusic(!AssetManager::get().isMusicMuted());
    std::string mute = AssetManager::get().isMusicMuted() ? "true" : "false";
    menuManager->UpdateText("Mute", "MUTE : " + mute);
    m_isclicked = true;
}


void MainMenuScene::Back()
{
    auto nameMenu = menuManager->GetCurrentMenu()->GetName();
    if (nameMenu == "Options")
    {
        menuManager->SetCurrentMenu("MainMenu");
        menuManager->RemoveMenu("Options");
    }
    else if (nameMenu == "Controls" || nameMenu == "Resolution" || nameMenu == "Volume")
    {
        menuManager->SetCurrentMenu("Options");
        menuManager->RemoveMenu(nameMenu);
    }
    m_isclicked = true;
}

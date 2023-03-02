#include "MainMenuScene.hpp"
#include <iostream>

MainMenuScene::MainMenuScene(Engine& engine) :Scene(engine)
{

    ui = new UI();
//    music = new sf::Music();
    menuManager = new MenuManager();
    assetManager = new AssetManager();
    m_input = &engine.getInputHandler();

    if (!videoTexture.loadFromFile("../../../../assets/wallpaper.jpg"))
    {
        std::cout << "Failed to load video" << std::endl;
        return;
    }
    assetManager->loadFont("shanghai", "../../../../assets/font/shanghai.ttf");

    assetManager->loadMusic("music", "../../../../assets/sound/Dragon.ogg");

    videoSprite.setTexture(videoTexture);
    videoSprite.setScale({ (float)2560 / (float)videoSprite.getTexture()->getSize().x, (float)1600 / (float)videoSprite.getTexture()->getSize().y });
   
    ui->CreateText("PlayButton", sf::Color::White, "PLAY", 300, sf::Vector2f(400, 200), *assetManager->getFont("shanghai"));
    ui->CreateText("OptionsButton", sf::Color::White, "OPTIONS", 200, sf::Vector2f(400, 525), *assetManager->getFont("shanghai"));
    ui->CreateText("QuitButton", sf::Color::White, "QUIT", 200, sf::Vector2f(400, 800), *assetManager->getFont("shanghai"));

    // create mainmenu menu shared pointer
    std::shared_ptr<Menu> mainMenu = std::make_shared<Menu>("MainMenu");
    mainMenu->AddButton("PlayButton");
    mainMenu->AddButton("OptionsButton");
    mainMenu->AddButton("QuitButton");
    menuManager->AddMenu(mainMenu);
    menuManager->SetCurrentMenu("MainMenu");

}

MainMenuScene::~MainMenuScene()
{
//    delete music;
//    music = nullptr;
    delete ui;
    ui = nullptr;
    delete menuManager;
    menuManager = nullptr;
    delete assetManager;
    assetManager = nullptr;
}

void MainMenuScene::Start()
{
    assetManager->setSoundVolume(2);
    assetManager->playMusic("music");
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
        if (menuManager->GetCurrentMenu()->GetName() == "MainMenu") {
            if (ui->InteractionButton("PlayButton", mousepos)) Play();
            if (ui->InteractionButton("QuitButton", mousepos)) Quit();
            if (ui->InteractionButton("OptionsButton", mousepos)) Options();
        }
        else if (menuManager->GetCurrentMenu()->GetName() == "Options")
        {
            if (ui->InteractionButton("ResolutionButton", mousepos)) Resolution();
            if (ui->InteractionButton("ControlsButton", mousepos)) Controls();
            if (ui->InteractionButton("VolumeButton", mousepos)) Back();
            if (ui->InteractionButton("BackButton", mousepos)) Back();
        }
        else if (menuManager->GetCurrentMenu()->GetName() == "Resolution")
        {
            if (ui->InteractionButton("2560x1600", mousepos)) SetResolution(2560, 1600);
            if (ui->InteractionButton("1920x1080", mousepos)) SetResolution(1600, 900);
            if (ui->InteractionButton("1280x720", mousepos)) SetResolution(1280, 720);
            if (ui->InteractionButton("BackButton", mousepos)) Back();
        }
        else if (menuManager->GetCurrentMenu()->GetName() == "Controls")
        {
            if (m_is_remap){
                // if not clicked or esc or enter
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) CancelRemap();
                else Remap();
            }
            if (ui->InteractionButton("BackButton", mousepos)) Back();
            if (ui->InteractionButton("MOVEUP", mousepos)) 
                UpdateInput(Action::MoveUp, "MOVEUP");
            if (ui->InteractionButton("MOVEDOWN", mousepos)) UpdateInput(Action::MoveDown, "MOVEDOWN");
            if (ui->InteractionButton("MOVELEFT", mousepos)) UpdateInput(Action::MoveLeft, "MOVELEFT");
            if (ui->InteractionButton("MOVERIGHT", mousepos)) UpdateInput(Action::MoveRight, "MOVERIGHT");
            if (ui->InteractionButton("ACTION", mousepos)) UpdateInput(Action::Action, "ACTION");
            if (ui->InteractionButton("JUMP", mousepos)) UpdateInput(Action::Jump, "JUMP");
        }
    }
}



void MainMenuScene::Render(sf::RenderTarget* renderTarget)
{
    renderTarget->draw(videoSprite);
    for(auto& button : menuManager->GetCurrentMenu()->GetButtons())
    {
        int i = ui->TextExist(button);
        if (i > -1) renderTarget->draw(ui->Text(i));
    }
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
    ui->CreateText("BackButton", sf::Color::White, "BACK", 200, sf::Vector2f(400, 900), *assetManager->getFont("shanghai"));
    ui->CreateText("ResolutionButton", sf::Color::White, "RESOLUTION", 200, sf::Vector2f(400, 525), *assetManager->getFont("shanghai"));
    ui->CreateText("ControlsButton", sf::Color::White, "CONTROLS", 200, sf::Vector2f(400, 300), *assetManager->getFont("shanghai"));
    ui->CreateText("VolumeButton", sf::Color::White, "VOLUME", 200, sf::Vector2f(400, 750), *assetManager->getFont("shanghai"));

    std::shared_ptr<Menu> optionsMenu = std::make_shared<Menu>("Options");
    optionsMenu->AddButton("BackButton");
    optionsMenu->AddButton("ResolutionButton");
    optionsMenu->AddButton("ControlsButton");
    optionsMenu->AddButton("VolumeButton");
    menuManager->AddMenu(optionsMenu);
    menuManager->SetCurrentMenu("Options");

    m_isclicked = true;
}

void MainMenuScene::Controls()
{
    std::cout << "Controls pressed" << std::endl;
    m_isclicked = true;

    ui->CreateText("MOVEUP", sf::Color::White, "UP : " + m_input->fromKtoS(m_input->getActionKey(Action::MoveUp)), 100, sf::Vector2f(400, 300), *assetManager->getFont("shanghai"));
    ui->CreateText("MOVEDOWN", sf::Color::White, "DOWN : " + m_input->fromKtoS(m_input->getActionKey(Action::MoveDown)), 100, sf::Vector2f(400, 400), *assetManager->getFont("shanghai"));
    ui->CreateText("MOVELEFT", sf::Color::White, "LEFT : " + m_input->fromKtoS(m_input->getActionKey(Action::MoveLeft)), 100, sf::Vector2f(400, 500), *assetManager->getFont("shanghai"));
    ui->CreateText("MOVERIGHT", sf::Color::White, "RIGHT : " + m_input->fromKtoS(m_input->getActionKey(Action::MoveRight)), 100, sf::Vector2f(400, 600), *assetManager->getFont("shanghai"));
    ui->CreateText("ACTION", sf::Color::White, "ACTION : " + m_input->fromKtoS(m_input->getActionKey(Action::Action)), 100, sf::Vector2f(400, 700), *assetManager->getFont("shanghai"));
    ui->CreateText("JUMP", sf::Color::White, "JUMP : " + m_input->fromKtoS(m_input->getActionKey(Action::Jump)), 100, sf::Vector2f(400, 800), *assetManager->getFont("shanghai"));

    std::shared_ptr<Menu> controlsMenu = std::make_shared<Menu>("Controls");
    controlsMenu->AddButton({"MOVEUP", "MOVEDOWN", "MOVELEFT", "MOVERIGHT", "ACTION", "JUMP", "BackButton"});
    menuManager->AddMenu(controlsMenu);
    menuManager->SetCurrentMenu("Controls");
}



void MainMenuScene::UpdateInput(Action action, std::string buttonName)
{
    std::cout << "UpdateInput" << std::endl;
    std::string text = buttonName + " : ";
    ui->CreateText("UpdateText", sf::Color::White, "Update", 100, sf::Vector2f(400, 400), *assetManager->getFont("shanghai"));
    menuManager->GetCurrentMenu()->AddButton("UpdateText");
    m_isclicked = true;
    m_is_remap = true;
    m_actionToRemap = action;
}

void MainMenuScene::Remap()
{
    for(sf::Keyboard::Key key = sf::Keyboard::A; key <= sf::Keyboard::KeyCount; key = sf::Keyboard::Key(key + 1))
    {
        if(sf::Keyboard::isKeyPressed(key))
        {
            m_is_remap = false;
            m_isclicked = false;
            std::cout << "Remap : "<< m_input->fromKtoS(key) << std::endl;
            m_input->remapAction(m_actionToRemap, key);

            switch (m_actionToRemap) {
                case Action::MoveUp:
                    ui->Text("MOVEUP").setString("UP : " + m_input->fromKtoS(key));
                    break;
                case Action::MoveDown:
                    ui->Text("MOVEDOWN").setString("DOWN : " + m_input->fromKtoS(key));
                    break;
                case Action::MoveLeft:
                    ui->Text("MOVELEFT").setString("LEFT : " + m_input->fromKtoS(key));
                    break;
                case Action::MoveRight:
                    ui->Text("MOVERIGHT").setString("RIGHT : " + m_input->fromKtoS(key));
                    break;
                case Action::Action:
                    ui->Text("Action").setString("ACTION : " + m_input->fromKtoS(key));
                    break;
                case Action::Jump:
                    ui->Text("Jump").setString("JUMP : " + m_input->fromKtoS(key));
                    break;
                default:
                    break;
            }



            ui->RemoveText("UpdateText");
        }
    }
}

void MainMenuScene::CancelRemap() {
    m_is_remap = false;
    m_isclicked = false;
    ui->RemoveText("UpdateText");
}



void MainMenuScene::Back()
{
    auto nameMenu = menuManager->GetCurrentMenu()->GetName();

    if (nameMenu == "Options")
    {
        for (auto& button : menuManager->GetCurrentMenu()->GetButtons())
        {
            ui->RemoveText(button);
        }
        menuManager->RemoveMenu("Options");
        menuManager->SetCurrentMenu("MainMenu");
    }
    else if (nameMenu == "Controls" || nameMenu == "Resolution")
    {
        for (auto& button : menuManager->GetCurrentMenu()->GetButtons())
        {
            if(button != "BackButton") ui->RemoveText(button);
        }
        menuManager->RemoveMenu(nameMenu);
        menuManager->SetCurrentMenu("Options");
    }
    m_isclicked = true;
}

void MainMenuScene::Resolution()
{
    std::cout << "Resolution pressed" << std::endl;
    m_isclicked = true;

    ui->CreateText("2560x1600", sf::Color::White, "2560x1600", 100, sf::Vector2f(400, 750), *assetManager->getFont("shanghai"));
    ui->CreateText("1920x1080", sf::Color::White, "1920x1080", 100, sf::Vector2f(400, 525), *assetManager->getFont("shanghai"));
    ui->CreateText("1280x720", sf::Color::White, "1280x720", 100, sf::Vector2f(400, 300), *assetManager->getFont("shanghai"));

    std::shared_ptr<Menu> resolutionMenu = std::make_shared<Menu>("Resolution");
    resolutionMenu->AddButton({"2560x1600", "1920x1080", "1280x720", "BackButton"});
    menuManager->AddMenu(resolutionMenu);
    menuManager->SetCurrentMenu("Resolution");

}

void MainMenuScene::SetResolution(int width, int height)
{
    engine->getRenderWindow().setSize(sf::Vector2u(width, height));
    videoSprite.setScale({ (float)width / (float)videoSprite.getTexture()->getSize().x, (float)height / (float)videoSprite.getTexture()->getSize().y });
    videoSprite.setPosition(0, 0);
}

void MainMenuScene::Volume() {
    std::cout << "Volume pressed" << std::endl;
    m_isclicked = true;
    ui->CreateText("ReduceVolume", sf::Color::White, "-", 100, sf::Vector2f(400, 300), *assetManager->getFont("shanghai"));
    ui->CreateText("Volume", sf::Color::White, "VOLUME", 100, sf::Vector2f(400, 400), *assetManager->getFont("shanghai"));
    ui->CreateText("IncreaseVolume", sf::Color::White, "+", 100, sf::Vector2f(400, 500), *assetManager->getFont("shanghai"));
    ui->CreateText("Mute", sf::Color::White, "MUTE : Off", 100, sf::Vector2f(400, 600), *assetManager->getFont("shanghai"));

    std::shared_ptr<Menu> volumeMenu = std::make_shared<Menu>("Volume");
    volumeMenu->AddButton({"ReduceVolume", "IncreaseVolume", "Mute", "BackButton"});
    menuManager->AddMenu(volumeMenu);
    menuManager->SetCurrentMenu("Volume");
}

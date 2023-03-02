#include "MainMenuScene.hpp"
#include <iostream>

MainMenuScene::MainMenuScene(Engine& engine) :Scene(engine)
{

    ui = std::make_shared<UI>();
    m_input = &engine.getInputHandler();

    if (!videoTexture.loadFromFile("../../../../assets/wallpaper.jpg"))
    {
        std::cout << "Failed to load video" << std::endl;
        return;
    }
    AssetManager::get().loadFont("Varnished", "../../../../assets/font/Varnished.ttf");
    menuManager = new MenuManager(ui, *AssetManager::get().getFont("Varnished"));

    AssetManager::get().loadMusic("music", "../../../../assets/sound/Dragon.ogg");

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

    menuManager->AddText("BackOptionsButton", sf::Color::White, "BACK", 200, sf::Vector2f(400, 900), [&]{ Back(); });
    menuManager->AddText("ResolutionButton", sf::Color::White, "RESOLUTION", 200, sf::Vector2f(400, 525), [&]{ Resolution(); });
    menuManager->AddText("ControlsButton", sf::Color::White, "CONTROLS", 200, sf::Vector2f(400, 300), [&]{ Controls(); });
    menuManager->AddText("VolumeButton", sf::Color::White, "VOLUME", 200, sf::Vector2f(400, 750), [&]{ Volume(); });

    m_isclicked = true;
}

void MainMenuScene::Controls()
{
    std::cout << "Controls pressed" << std::endl;
    m_isclicked = true;
    std::shared_ptr<Menu> controlsMenu = std::make_shared<Menu>("Controls");
    menuManager->AddMenu(controlsMenu);
    menuManager->SetCurrentMenu("Controls");

    menuManager->AddText("MOVEUP", sf::Color::White, "UP : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveUp)), 100, sf::Vector2f(400, 300), [&]{ UpdateInput(EInput::MoveUp, "MOVEUP"); });
    menuManager->AddText("MOVEDOWN", sf::Color::White, "DOWN : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveDown)), 100, sf::Vector2f(400, 400), [&]{ UpdateInput(EInput::MoveDown, "MOVEDOWN"); });
    menuManager->AddText("MOVELEFT", sf::Color::White, "LEFT : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveLeft)), 100, sf::Vector2f(400, 500), [&]{ UpdateInput(EInput::MoveLeft, "MOVELEFT"); });
    menuManager->AddText("MOVERIGHT", sf::Color::White, "RIGHT : " + m_input->fromKtoS(m_input->getActionKey(EInput::MoveRight)), 100, sf::Vector2f(400, 600), [&]{ UpdateInput(EInput::MoveRight, "MOVERIGHT"); });
    menuManager->AddText("ACTION", sf::Color::White, "ACTION : " + m_input->fromKtoS(m_input->getActionKey(EInput::Action)), 100, sf::Vector2f(400, 700), [&]{ UpdateInput(EInput::Action, "ACTION"); });
    menuManager->AddText("JUMP", sf::Color::White, "JUMP : " + m_input->fromKtoS(m_input->getActionKey(EInput::Jump)), 100, sf::Vector2f(400, 800), [&]{ UpdateInput(EInput::Jump, "JUMP"); });
    menuManager->AddText("BackControlsButton", sf::Color::White, "BACK", 200, sf::Vector2f(400, 900), [&]{ Back(); });

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
                case EInput::MoveUp:
                    menuManager->UpdateText("MOVEUP", "UP : " + m_input->fromKtoS(key));
                    break;
                case EInput::MoveDown:
                    menuManager->UpdateText("MOVEDOWN", "DOWN : " + m_input->fromKtoS(key));
                    break;
                case EInput::MoveLeft:
                    menuManager->UpdateText("MOVELEFT", "LEFT : " + m_input->fromKtoS(key));
                    break;
                case EInput::MoveRight:
                    menuManager->UpdateText("MOVERIGHT", "RIGHT : " + m_input->fromKtoS(key));
                    break;
                case EInput::Action:
                    menuManager->UpdateText("ACTION", "ACTION : " + m_input->fromKtoS(key));
                    break;
                case EInput::Jump:
                    menuManager->UpdateText("Jump", "JUMP : " + m_input->fromKtoS(key));
                    break;
                default:
                    break;
            }

            menuManager->RemoveText("UpdateText");
            menuManager->RemoveZone("UpdateZone");
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

    menuManager->AddText("ReduceVolume", sf::Color::White, "-", 200, sf::Vector2f(200, 400), [&]{ ReduceVolume(); });
    menuManager->AddText("Volume", sf::Color::White, "VOLUME : " + std::to_string(AssetManager::get().getSoundVolume()), 100, sf::Vector2f(600, 400), [&]{ });
    menuManager->AddText("IncreaseVolume", sf::Color::White, "+", 200, sf::Vector2f(1000, 400), [&]{ IncreaseVolume(); });
    menuManager->AddText("Mute", sf::Color::White, "MUTE : " + std::to_string(AssetManager::get().isMusicMuted()), 100, sf::Vector2f(400, 600), [&]{ Mute(); });
    menuManager->AddText("BackVolumeButton", sf::Color::White, "BACK", 200, sf::Vector2f(400, 900), [&]{ Back(); });

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
    menuManager->UpdateText("Volume", "MUTE : " + mute);
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

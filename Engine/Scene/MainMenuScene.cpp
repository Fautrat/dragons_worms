#include "MainMenuScene.hpp"
#include <iostream>

MainMenuScene::MainMenuScene(Engine& engine) :Scene(engine)
{

    ui = new UI();
    music = new sf::Music();
    menuManager = new MenuManager();

    if (!videoTexture.loadFromFile("../../../../assets/wallpaper.jpg"))
    {
        std::cout << "Failed to load video" << std::endl;
        return;
    }
    if (!font.loadFromFile("../../../../assets/font/shanghai.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
        return;
    }
    if (!music->openFromFile("../../../../assets/sound/Dragon.ogg"))
    {
        std::cout << "Failed to load music" << std::endl;
        return;
    }


    videoSprite.setTexture(videoTexture);
    videoSprite.setScale({ (float)2560 / (float)videoSprite.getTexture()->getSize().x, (float)1600 / (float)videoSprite.getTexture()->getSize().y });
   
    ui->CreateText("PlayButton", sf::Color::White, "PLAY", 300, sf::Vector2f(400, 200), font);
    ui->CreateText("OptionsButton", sf::Color::White, "OPTIONS", 200, sf::Vector2f(400, 525), font);
    ui->CreateText("QuitButton", sf::Color::White, "QUIT", 200, sf::Vector2f(400, 800), font);

    // create mainmenu menu shared pointer
    std::shared_ptr<Menu> mainMenu = std::make_shared<Menu>("MainMenu");
    mainMenu->AddButton("PlayButton");
    mainMenu->AddButton("OptionsButton");
    mainMenu->AddButton("QuitButton");
    menuManager->AddMenu(mainMenu);
    menuManager->SetCurrentMenu("MainMenu");


    music->setVolume(20);


}

MainMenuScene::~MainMenuScene()
{
    delete music;
    music = nullptr;
    delete ui;
    ui = nullptr;
    delete menuManager;
    menuManager = nullptr;
}

void MainMenuScene::Start()
{
    music->play();
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
            if (ui->InteractionButton("BackButton", mousepos)) Back();

        }
    }
}

void MainMenuScene::Render(sf::RenderTarget* renderTarget)
{
    renderTarget->draw(videoSprite);
    for(auto& button : menuManager->GetCurrentMenu()->GetButtons())
    {
        renderTarget->draw(ui->Text(button));
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
    ui->CreateText("BackButton", sf::Color::White, "BACK", 200, sf::Vector2f(400, 900), font);
    ui->CreateText("ResolutionButton", sf::Color::White, "RESOLUTION", 200, sf::Vector2f(400, 525), font);
    ui->CreateText("ControlsButton", sf::Color::White, "CONTROLS", 200, sf::Vector2f(400, 300), font);
    ui->CreateText("VolumeButton", sf::Color::White, "VOLUME", 200, sf::Vector2f(400, 750), font);

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

    ui->CreateText("UP", sf::Color::White, "UP : Z", 100, sf::Vector2f(400, 300), font);
    ui->CreateText("DOWN", sf::Color::White, "DOWN : S", 100, sf::Vector2f(400, 400), font);
    ui->CreateText("LEFT", sf::Color::White, "LEFT : Q", 100, sf::Vector2f(400, 500), font);
    ui->CreateText("RIGHT", sf::Color::White, "RIGHT : D", 100, sf::Vector2f(400, 600), font);
    ui->CreateText("ATTACK", sf::Color::White, "ATTACK : CTRL", 100, sf::Vector2f(400, 700), font);
    ui->CreateText("JUMP", sf::Color::White, "JUMP : SPACE", 100, sf::Vector2f(400, 800), font);

    std::shared_ptr<Menu> controlsMenu = std::make_shared<Menu>("Controls");
    controlsMenu->AddButton({"UP", "DOWN", "LEFT", "RIGHT", "ATTACK", "JUMP", "BackButton"});
    menuManager->AddMenu(controlsMenu);
    menuManager->SetCurrentMenu("Controls");
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

    ui->CreateText("2560x1600", sf::Color::White, "2560x1600", 100, sf::Vector2f(400, 750), font);
    ui->CreateText("1920x1080", sf::Color::White, "1920x1080", 100, sf::Vector2f(400, 525), font);
    ui->CreateText("1280x720", sf::Color::White, "1280x720", 100, sf::Vector2f(400, 300), font);

    std::shared_ptr<Menu> resolutionMenu = std::make_shared<Menu>("Resolution");
    resolutionMenu->AddButton({"2560x1600", "1920x1080", "1280x720", "BackButton"});
    menuManager->AddMenu(resolutionMenu);
    menuManager->SetCurrentMenu("Resolution");

}

void MainMenuScene::SetResolution(int width, int height)
{
    videoSprite.setScale({ (float)width / (float)videoSprite.getTexture()->getSize().x, (float)height / (float)videoSprite.getTexture()->getSize().y });
    videoSprite.setPosition(0, 0);
    engine->getRenderWindow().setSize(sf::Vector2u(width, height));
}

void MainMenuScene::Volume() {
    std::cout << "Volume pressed" << std::endl;
    m_isclicked = true;
    ui->CreateText("ReduceVolume", sf::Color::White, "-", 100, sf::Vector2f(400, 300), font);
    ui->CreateText("Volume", sf::Color::White, "VOLUME", 100, sf::Vector2f(400, 400), font);
    ui->CreateText("IncreaseVolume", sf::Color::White, "+", 100, sf::Vector2f(400, 500), font);
    ui->CreateText("Mute", sf::Color::White, "MUTE : Off", 100, sf::Vector2f(400, 600), font);

}

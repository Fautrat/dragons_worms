#include "MainMenuScene.hpp"
#include <iostream>

MainMenuScene::MainMenuScene(Engine& engine) :Scene(engine)
{

    ui = new UI();
    music = new sf::Music();

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
    videoSprite.setScale({ (float)1920 / (float)videoSprite.getTexture()->getSize().x, (float)1080 / (float)videoSprite.getTexture()->getSize().y });
   
    ui->CreateText("PlayButton", sf::Color::White, "PLAY", 300, sf::Vector2f(400, 400), font);
    ui->CreateText("QuitButton", sf::Color::White, "QUIT", 200, sf::Vector2f(400, 740), font);

    music->setVolume(20);


}

MainMenuScene::~MainMenuScene()
{
    delete music;
    music = nullptr;
    delete ui;
    ui = nullptr;
}

void MainMenuScene::Start()
{
    music->play();
}

void MainMenuScene::Update(const float& deltaTime)
{
   
    sf::Vector2i mousepos = engine->getMousePos();
    if (ui->InteractionButton("PlayButton", mousepos)) Play();
    if (ui->InteractionButton("QuitButton", mousepos)) Quit();
    
}

void MainMenuScene::Render(sf::RenderTarget* renderTarget)
{
    renderTarget->draw(videoSprite);
    renderTarget->draw(ui->Text("PlayButton"));
    renderTarget->draw(ui->Text("QuitButton"));

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

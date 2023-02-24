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
    if (!music->openFromFile("../../../../assets/sound/Dragon.ogg"))
    {
        std::cout << "Failed to load music" << std::endl;
        return;
    }


    videoSprite.setTexture(videoTexture);
    videoSprite.setScale({ (float)1920 / (float)videoSprite.getTexture()->getSize().x, (float)1080 / (float)videoSprite.getTexture()->getSize().y });
   
    ui->CreateText("PlayButton", sf::Color::White, "PLAY", 300, sf::Vector2f(400, 200), ui->getFont());
    ui->CreateText("OptionsButton", sf::Color::White, "OPTIONS", 200, sf::Vector2f(400, 525), ui->getFont());
    ui->CreateText("QuitButton", sf::Color::White, "QUIT", 200, sf::Vector2f(400, 800), ui->getFont());

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
    if (ui->InteractionButton("OptionsButton", mousepos)) Options();
       
}

void MainMenuScene::Render(sf::RenderTarget* renderTarget)
{
    renderTarget->draw(videoSprite);
    renderTarget->draw(ui->Text("PlayButton"));
    renderTarget->draw(ui->Text("OptionsButton"));
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

void MainMenuScene::Options()
{
    std::cout << "Options pressed" << std::endl;
}

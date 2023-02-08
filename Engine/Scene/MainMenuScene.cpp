#include "MainMenuScene.hpp"
#include <iostream>

MainMenuScene::MainMenuScene(Engine& engine) :Scene(engine)
{
    
    ui = new UI();
    ui->CreateText("PlayButton", sf::Color::White, "PLAY", 300, sf::Vector2f(200, 400), font);
    ui->CreateText("QuitButton", sf::Color::White, "QUIT", 200, sf::Vector2f(200, 740), font);
    if (!videoTexture.loadFromFile("../../../../assets/wallpaper.jpg"))
    {
        std::cout << "Failed to load video" << std::endl;
        return;
    }

    videoSprite.setTexture(videoTexture);
    videoSprite.setScale({ (float)1920 / (float)videoSprite.getTexture()->getSize().x, (float)1080 / (float)videoSprite.getTexture()->getSize().y });
    font.loadFromFile("../../../../assets/font/shanghai.ttf");
    ui->CreateText("PlayButton", sf::Color::White, "PLAY", 300, sf::Vector2f(960, 400), font);
    ui->CreateText("QuitButton", sf::Color::White, "QUIT", 200, sf::Vector2f(960, 740), font);


}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::Start()
{
 
   
}

void MainMenuScene::Update(const float& deltaTime)
{

}

void MainMenuScene::Render(sf::RenderTarget* renderTarget)
{
    renderTarget->draw(videoSprite);
    renderTarget->draw(ui->Text("PlayButton"));
    renderTarget->draw(ui->Text("QuitButton"));

}
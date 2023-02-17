#include "InGameScene.hpp"
#include <iostream>

InGameScene::InGameScene(Engine& engine) :Scene(engine)
{
    if (!backgroundTexture.loadFromFile("../../../../assets/Maps/background1.png"))
    {
        std::cout << "Failed to load background" << std::endl;
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);
    //TODO : changer les valeurs en dur
    backgroundSprite.setScale({ (float)1920 / (float)backgroundSprite.getTexture()->getSize().x, (float)1080 / (float)backgroundSprite.getTexture()->getSize().y });
    

    AssetManagerTemp::get().loadTexture("Player", "../../../../assets/Dragon/dragon_testsprite.png");

    m_manager = new EntityManager();
    Entity* entity = new Entity();
    entity->getComponent<Transform>().position = sf::Vector2f(100, 100);
    entity->addComponent<SpriteRenderer>("Player");
    m_manager->addEntity(entity);
}

InGameScene::~InGameScene()
{
    delete player;
}

void InGameScene::Start()
{
    player = new Dragon(&engine->getInputHandler()); 
}

void InGameScene::Update(const float& deltaTime)
{
    m_manager->update();
    player->update(&engine->getRenderWindow());
}

void InGameScene::Render(sf::RenderTarget* renderTarget)
{
    m_manager->draw(renderTarget);
    renderTarget->draw(backgroundSprite);
    if(&player->getShape())
    renderTarget->draw(player->getShape());

}
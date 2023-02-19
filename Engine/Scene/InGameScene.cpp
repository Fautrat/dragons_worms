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
    
    //PLAYER WITH GRAVITY AND COLLISION
    AssetManagerTemp::get().loadTexture("Player", "../../../../assets/Dragon/dragon_testsprite.png");
    m_manager = new EntityManager();
    
    dragon->addComponent<Transform>(100, 100, 1, 1);
    dragon->addComponent<Rigidbody>(1);
    dragon->addComponent<SpriteRenderer>("Player");
    dragon->addComponent<BoxCollider2D>(
        AssetManagerTemp::get().getTexture("Player")->getSize().x * dragon->getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManagerTemp::get().getTexture("Player")->getSize().y * dragon->getComponent<SpriteRenderer>().getSprite()->getScale().y);
    m_manager->addEntity(dragon);

    //WALL FOR TEST COLLISION
    AssetManagerTemp::get().loadTexture("Wall", "../../../../assets/Dragon/wall.png");
    
    wall->addComponent<Transform>(100, 500, 1, 3);
    wall->addComponent<SpriteRenderer>("Wall");
    wall->addComponent<BoxCollider2D>(
        AssetManagerTemp::get().getTexture("Wall")->getSize().x * wall->getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManagerTemp::get().getTexture("Wall")->getSize().y * wall->getComponent<SpriteRenderer>().getSprite()->getScale().y
        );
    m_manager->addEntity(wall);





    
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
    auto lastPos = dragon->getComponent<Transform>().position;

    m_manager->refresh();
    m_manager->update();
    auto v = dragon->getComponent<Transform>().position;
    std::string log = "Transform (" + std::to_string(v.x) + " " + std::to_string(v.y) + ")";
    
    if (collision->BoxAndBox(dragon->getComponent<BoxCollider2D>().getBox(), wall->getComponent<BoxCollider2D>().getBox()))
    {
        dragon->getComponent<Transform>().position = lastPos;
    }

    
    
    
    
    
    player->update(&engine->getRenderWindow());
}

void InGameScene::Render(sf::RenderTarget* renderTarget)
{ 
    renderTarget->draw(backgroundSprite);
    if(&player->getShape())
    renderTarget->draw(player->getShape());
    m_manager->draw(renderTarget);
}
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

}

InGameScene::~InGameScene()
{
    delete player;   
}

void InGameScene::Start()
{
    //player = new Dragon(&engine->getInputHandler()); 

    //PLAYER WITH GRAVITY AND COLLISION
    AssetManager::get().loadTexture("Player", "../../../../assets/Dragon/dragon.png");
    m_manager = new EntityManager();
    dragon.addComponent<Transform>(500, 100, 1, 1);
    dragon.addComponent<Rigidbody>(1);
    dragon.addComponent<SpriteRenderer>("Player");
    dragon.addComponent<BoxCollider2D>(
        AssetManager::get().getTexture("Player")->getSize().x * dragon.getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManager::get().getTexture("Player")->getSize().y * dragon.getComponent<SpriteRenderer>().getSprite()->getScale().y);
    dragon.addComponent<Input>(&engine->getInputHandler());
    m_manager->addEntity(&dragon);

    //WALL FOR TEST COLLISION
    AssetManager::get().loadTexture("Wall", "../../../../assets/Dragon/wall.png");
    wall.addComponent<Transform>(0, 1000, 10, 1);
    wall.addComponent<SpriteRenderer>("Wall");
    wall.addComponent<BoxCollider2D>(
        AssetManager::get().getTexture("Wall")->getSize().x * wall.getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManager::get().getTexture("Wall")->getSize().y * wall.getComponent<SpriteRenderer>().getSprite()->getScale().y
        );
    m_manager->addEntity(&wall);

    //CiRCLE FOR TEST COLLISION
    AssetManager::get().loadTexture("Circle", "../../../../assets/Dragon/Circle.png");
    circle.addComponent<Transform>(500, 100, 1, 1);
    circle.addComponent<SpriteRenderer>("Circle");
    circle.addComponent<SphereCollider2D>(
        (AssetManager::get().getTexture("Circle")->getSize().x * circle.getComponent<SpriteRenderer>().getSprite()->getScale().x) / 2,
        AssetManager::get().getTexture("Circle")->getSize().x * circle.getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManager::get().getTexture("Circle")->getSize().y * circle.getComponent<SpriteRenderer>().getSprite()->getScale().y);
    circle.addComponent<Rigidbody>(1);
    //m_manager->addEntity(&circle);

    //Triangle FOR TEST COLLISION
    AssetManager::get().loadTexture("Triangle", "../../../../assets/Dragon/TRIANGLE.png");
    Triangle.addComponent<Transform>(450, 550, 1, 1);
    Triangle.addComponent<SpriteRenderer>("Triangle");
    Triangle.addComponent<TriangleCollider2D>(AssetManager::get().getTexture("Triangle")->getSize().x * Triangle.getComponent<SpriteRenderer>().getSprite()->getScale().x, DOWNRIGHT);
    m_manager->addEntity(&Triangle);

    Map* map = new Map();
    

}

void InGameScene::Update(const float& deltaTime)
{
    auto lastPosDrag = dragon.getComponent<Transform>().position.y;
    auto lastPosCircle = circle.getComponent<Transform>().position.y;
    auto lastPosDragx = dragon.getComponent<Transform>().position.x;
    m_manager->refresh();
    m_manager->update(deltaTime);
    auto v = dragon.getComponent<Transform>().position;
    std::string log = "Transform (" + std::to_string(v.x) + " " + std::to_string(v.y) + ")";
    
  /*  if (collision->BoxAndBox(dragon.getComponent<BoxCollider2D>(), wall.getComponent<BoxCollider2D>()) )
    {
          dragon->getComponent<Transform>().position.y = lastPos;
          dragon->getComponent<Rigidbody>().setVelocityY(0.f);
          dragon->getComponent<Rigidbody>().landing();
    }

    if (collision->SphereAndBox(circle.getComponent<SphereCollider2D>(), wall.getComponent<BoxCollider2D>()))
    {
            circle.getComponent<Transform>().position.y = lastPosCircle;
    }


    if (collision->SphereAndBox(circle.getComponent<SphereCollider2D>(), dragon.getComponent<BoxCollider2D>()))
    {
        dragon.getComponent<Transform>().position.x = lastPosDragx;
    }

    if (collision->TriangleAndSphere(Triangle.getComponent<TriangleCollider2D>(), circle.getComponent<SphereCollider2D>()))
    {
        circle.getComponent<Transform>().position.y = lastPosCircle;
    }*/
    
   // player->update(&engine->getRenderWindow());
}

void InGameScene::Render(sf::RenderTarget* renderTarget)
{ 
    renderTarget->draw(backgroundSprite);
    /*if(&player->getShape())
    renderTarget->draw(player->getShape());
    */
    m_manager->draw(renderTarget);
}
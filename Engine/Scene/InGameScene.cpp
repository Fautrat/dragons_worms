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
    AssetManagerTemp::get().loadTexture("Player", "../../../../assets/Dragon/dragon_testsprite.png");
    m_manager = new EntityManager();
    dragon->addComponent<Transform>(100, 100, 1, 1);
    dragon->addComponent<Rigidbody>(1);
    dragon->addComponent<SpriteRenderer>("Player");
    dragon->addComponent<BoxCollider2D>(
        AssetManagerTemp::get().getTexture("Player")->getSize().x * dragon->getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManagerTemp::get().getTexture("Player")->getSize().y * dragon->getComponent<SpriteRenderer>().getSprite()->getScale().y);
    dragon->addComponent<Input>(&engine->getInputHandler());
    m_manager->addEntity(dragon);

    //WALL FOR TEST COLLISION
    AssetManagerTemp::get().loadTexture("Wall", "../../../../assets/Dragon/wall.png");
    wall->addComponent<Transform>(0, 1000, 10, 1);
    wall->addComponent<SpriteRenderer>("Wall");
    wall->addComponent<BoxCollider2D>(
        AssetManagerTemp::get().getTexture("Wall")->getSize().x * wall->getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManagerTemp::get().getTexture("Wall")->getSize().y * wall->getComponent<SpriteRenderer>().getSprite()->getScale().y
        );
    m_manager->addEntity(wall);

    //CiRCLE FOR TEST COLLISION
    AssetManagerTemp::get().loadTexture("Circle", "../../../../assets/Dragon/Circle.png");
    circle->addComponent<Transform>(500, 100, 1, 1);
    circle->addComponent<SpriteRenderer>("Circle");
    circle->addComponent<SphereCollider2D>(
        (AssetManagerTemp::get().getTexture("Circle")->getSize().x * circle->getComponent<SpriteRenderer>().getSprite()->getScale().x) / 2,
        AssetManagerTemp::get().getTexture("Circle")->getSize().x * circle->getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManagerTemp::get().getTexture("Circle")->getSize().y * circle->getComponent<SpriteRenderer>().getSprite()->getScale().y);
    circle->addComponent<Rigidbody>(1);
    m_manager->addEntity(circle);

    //Triangle FOR TEST COLLISION
    AssetManagerTemp::get().loadTexture("Triangle", "../../../../assets/Dragon/TRIANGLE.png");
    Triangle->addComponent<Transform>(450, 550, 2, 2);
    Triangle->addComponent<SpriteRenderer>("Triangle");
    int spriteWidth = AssetManagerTemp::get().getTexture("Triangle")->getSize().x * Triangle->getComponent<SpriteRenderer>().getSprite()->getScale().x;
    int posX = Triangle->getComponent<Transform>().position.x;
    int posY = Triangle->getComponent<Transform>().position.y;
    Triangle->addComponent<TriangleCollider2D>(
        sf::Vector2(sf::Vector2i(posX + spriteWidth, posY + spriteWidth),sf::Vector2i(posX,posY + spriteWidth)),
        sf::Vector2(sf::Vector2i(posX + spriteWidth, posY + spriteWidth),sf::Vector2i(posX, posY)),
        sf::Vector2(sf::Vector2i(posX, posY + spriteWidth),sf::Vector2i(posX,posY)),
        AssetManagerTemp::get().getTexture("Triangle")->getSize().x * Triangle->getComponent<SpriteRenderer>().getSprite()->getScale().x);
        m_manager->addEntity(Triangle);
}

void InGameScene::Update(const float& deltaTime)
{
    auto lastPosDrag = dragon->getComponent<Transform>().position.y;
    auto lastPosCircle = circle->getComponent<Transform>().position.y;
    auto lastPosDragx = dragon->getComponent<Transform>().position.x;
    m_manager->refresh();
    m_manager->update();
    auto v = dragon->getComponent<Transform>().position;
    std::string log = "Transform (" + std::to_string(v.x) + " " + std::to_string(v.y) + ")";
    
    if (collision->BoxAndBox(dragon->getComponent<BoxCollider2D>(), wall->getComponent<BoxCollider2D>()) )
    {
            dragon->getComponent<Transform>().position.y = lastPosDrag;
    }

    if (collision->SphereAndBox(circle->getComponent<SphereCollider2D>(), wall->getComponent<BoxCollider2D>()))
    {
            circle->getComponent<Transform>().position.y = lastPosCircle;
    }


    if (collision->SphereAndBox(circle->getComponent<SphereCollider2D>(), dragon->getComponent<BoxCollider2D>()))
    {
        dragon->getComponent<Transform>().position.x = lastPosDragx;
    }

    if (collision->TriangleAndSphere(Triangle->getComponent<TriangleCollider2D>(), circle->getComponent<SphereCollider2D>()))
    {
        circle->getComponent<Transform>().position.y = lastPosCircle;
    }
    
    
    
    
    
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
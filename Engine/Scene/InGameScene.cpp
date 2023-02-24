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
    ui = new UI();

    ui->CreateText("Timer", sf::Color::White, " ", 100, sf::Vector2f(900, 100), ui->getFont());
}

InGameScene::~InGameScene()
{
    delete m_manager;
    delete ui;
    delete collision;
}

void InGameScene::Start()
{

    //PLAYER WITH GRAVITY AND COLLISION
    AssetManager::get().loadTexture("Player", "../../../../assets/Dragon/dragon.png");
    m_manager = new EntityManager();
   /* player1.addComponent<Transform>(800, 100, 1, 1);
    player1.addComponent<Rigidbody>(1);
    player1.addComponent<SpriteRenderer>("Player");
    player1.addComponent<BoxCollider2D>(
        AssetManager::get().getTexture("Player")->getSize().x * player1.getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManager::get().getTexture("Player")->getSize().y * player1.getComponent<SpriteRenderer>().getSprite()->getScale().y);*/
    //player1.addComponent<Input>(&engine->getInputHandler());
    
    player3.addComponent<Transform>(800, 100, 1, 1);
    player3.addComponent<Rigidbody>(1);
    player3.addComponent<SpriteRenderer>("Player");
    player3.addComponent<BoxCollider2D>(
        AssetManager::get().getTexture("Player")->getSize().x * player3.getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManager::get().getTexture("Player")->getSize().y * player3.getComponent<SpriteRenderer>().getSprite()->getScale().y);
    player3.addComponent<LifeBar>();

    player3.connectInput(&engine->getInputHandler());

    m_manager = new EntityManager();
    player2.addComponent<Transform>(1400, 100, 1, 1);
    player2.addComponent<Rigidbody>(1);
    player2.addComponent<SpriteRenderer>("Player");
    player2.addComponent<BoxCollider2D>(
        AssetManager::get().getTexture("Player")->getSize().x * player2.getComponent<SpriteRenderer>().getSprite()->getScale().x,
        AssetManager::get().getTexture("Player")->getSize().y * player2.getComponent<SpriteRenderer>().getSprite()->getScale().y);
    //player2.addComponent<Input>(&engine->getInputHandler());
    player2.addComponent<LifeBar>();


    m_manager->addEntity(&player3);
    m_manager->addEntity(&player2);

    //WALL FOR TEST COLLISION
    AssetManager::get().loadTexture("Wall", "../../../../assets/Dragon/wall.png");
    wall.addComponent<Transform>(1000, 1000, 10, 1);
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

}

void InGameScene::Update(const float& deltaTime)
{
    auto lastPosDrag = player3.getComponent<Transform>().position.y;
    auto lastPosDrag2 = player2.getComponent<Transform>().position.y;
    auto lastPosCircle = circle.getComponent<Transform>().position.y;
    auto lastPosDragx = player3.getComponent<Transform>().position.x;
    m_manager->refresh();
    m_manager->update(deltaTime);
    
    if (collision->BoxAndBox(player3.getComponent<BoxCollider2D>(), wall.getComponent<BoxCollider2D>()) )
    {
        player3.getComponent<Transform>().position.y = lastPosDrag;
        player3.getComponent<Rigidbody>().setVelocityY(0.f);
        player3.getComponent<Rigidbody>().landing();
    }

    if (collision->BoxAndBox(player2.getComponent<BoxCollider2D>(), wall.getComponent<BoxCollider2D>()))
    {
        player2.getComponent<Transform>().position.y = lastPosDrag2;
        player2.getComponent<Rigidbody>().setVelocityY(0.f);
        player2.getComponent<Rigidbody>().landing();
    }

    if (deltaTime >= 1.f)
        timer--;

    if (timer < 0)
        newTurn();

    ui->Text("Timer").setString(std::to_string(timer));

    /* if (collision->SphereAndBox(circle.getComponent<SphereCollider2D>(), wall.getComponent<BoxCollider2D>()))
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
    renderTarget->draw(ui->Text("Timer"));
    m_manager->draw(renderTarget);
}

void InGameScene::newTurn()
{
    if (currentPlayer == WhosTurn::Player1)
    {
        player2.connectInput(&engine->getInputHandler());
        currentPlayer = Player2;
    }
    else
    {
        player3.connectInput(&engine->getInputHandler());
        currentPlayer = Player1;
    }

    timer = 10;
}
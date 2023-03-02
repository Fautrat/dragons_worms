#include "InGameScene.hpp"
#include <iostream>


InGameScene::InGameScene(Engine& engine) :Scene(engine) , m_manager(EntityManager::getInstance())
{
    if (!backgroundTexture.loadFromFile("../../../../assets/Maps/background1.png"))
    {
        std::cout << "Failed to load background" << std::endl;
        return;
    }
    AssetManager::get().loadFont("Shangai", "../../../../assets/font/shanghai.ttf");
    font = AssetManager::get().getFont("Shangai");

    backgroundSprite.setTexture(backgroundTexture);
    //TODO : changer les valeurs en dur
    backgroundSprite.setScale({ (float)1920 / (float)backgroundSprite.getTexture()->getSize().x, (float)1080 / (float)backgroundSprite.getTexture()->getSize().y });
    ui = new UI();
    collision = new Collision();

    ui->CreateText("Timer", sf::Color::White, " ", 100, sf::Vector2f(900, 100), *font);
}

InGameScene::~InGameScene()
{
    m_manager->killInstance();
    delete ui;
    delete collision;
}

void InGameScene::Start()
{
    AssetManager::get().loadTexture("Player", "../../../../assets/Dragon/dragon.png");
    /*AssetManager::get().loadTexture("Wall", "../../../../assets/Dragon/wall.png");
    AssetManager::get().loadTexture("Circle", "../../../../assets/Dragon/circle.png");
    AssetManager::get().loadTexture("Triangle", "../../../../assets/Dragon/triangle.png");*/

    player1.getComponent<Transform>()->setTransform(300.f, 0, 0, 0, 0.7f, 0.7f);
    /*player1.addComponent<SpriteRenderer>("Player");
    player1.addComponent<Rigidbody>(1, false, 0, 2);
    player1.addComponent<Collider2D>(BOX);
    player1.addComponent<LifeBar>();*/
    m_manager->addEntity(&player1);

    player1.connectInput(&engine->getInputHandler());

    player2.getComponent<Transform>()->setTransform(800.f, 0, 0, 0, 0.7f, 0.7f);
    /*player2.addComponent<SpriteRenderer>("Player");
    player2.addComponent<Rigidbody>(1, false, 0, 2);
    player2.addComponent<Collider2D>(BOX);
    player2.addComponent<LifeBar>();*/
    m_manager->addEntity(&player2);


  /*  circle2.getComponent<Transform>()->setTransform(0,300,0,0,0.5f,0.5f);
    circle2.getComponent<SpriteRenderer>()->flipTextureLeft();
    circle2.addComponent<SpriteRenderer>("Circle");
    circle2.addComponent<Rigidbody>(1, false, 1, 1);
    circle2.addComponent<Collider2D>(SPHERE);
    m_manager->addEntity(&circle2);*/ 

    //Triangle.getComponent<Transform>().setTransform(800, 872, 90, 0, 1, 1);
    //Triangle.addComponent<SpriteRenderer>("Triangle");
    //Triangle.addComponent<Rigidbody>(1, true, 1, 0);
    //Triangle.addComponent<Collider2D>(TRIANGLE);
    //m_manager->addEntity(&Triangle);


    //ground.getComponent<Transform>().setTransform(1000, 1000, 0, 0, 20, 1);
    //ground.addComponent<SpriteRenderer>("Wall");
    //ground.addComponent<Rigidbody>(1, true, 0.7, 0);
    //ground.addComponent<Collider2D>(BOX);
    //m_manager->addEntity(&ground);


    //// ADD ENTITY FOR PHYSICS CALCUL IN THE WORLD
   
    //worldptr->addEntityWithPhysics(Triangle);
    //worldptr->addEntityWithPhysics(ground);

    readMap();

    for (auto& tile : tileset)
    {
        auto entity = dynamic_cast<Entity*>(tile);
        m_manager->addEntity(entity);
       // worldptr->addEntityWithPhysics(*entity);
    }

   /* worldptr->addEntityWithPhysics(circle2);
    worldptr->addEntityWithPhysics(dragon);*/
}

void InGameScene::Update(const float& deltaTime)
{
    m_manager->update(deltaTime);
    //worldptr->updatePhysics(deltaTime);

    /* update timer */
    timer -= deltaTime;

    if (timer < 0 || players[currentPlayer]->turnEnding)
        newTurn();

    ui->Text("Timer").setString(std::to_string(static_cast<int>(timer)));
}

void InGameScene::Render(sf::RenderTarget* renderTarget)
{ 
    renderTarget->draw(backgroundSprite);
    m_manager->draw(renderTarget);

    renderTarget->draw(ui->Text("Timer"));
}

void InGameScene::newTurn()
{
    players[currentPlayer]->turnEnding = false;
    players[currentPlayer]->hasShoot = false;
    if (currentPlayer == WhosTurn::Player1)
        currentPlayer = Player2;
    else
        currentPlayer = Player1;

    players[currentPlayer]->connectInput(&engine->getInputHandler());
    timer = 10;
}

void InGameScene::readMap()
{
    char map_[] = {
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S',
                ' ',' ',' ',' ',' ',' ','S','S',' ',' ',' ',' ',' ','S','/',
                ' ',' ',' ',' ',' ','S','/','\\',' ',' ',' ',' ','S','/','-',
                ' ',' ',' ',' ','S','/','-','-','\\',' ',' ','S','/','-','-',
                'S','S','S','S','/','-','-','-','-','\\','S','/','-','-','-',
                '-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'
    };


    //active = true;
    int row = 10, col = 15;

    sf::Vector2f tile_size(1980.f / col, 1080.f / row);
    AssetManager::get().loadTexture("Dirt", "../../../../assets/dirt.png");
    AssetManager::get().loadTexture("Left_Diag", "../../../../assets/left_diag.png");
    AssetManager::get().loadTexture("Right_Diag", "../../../../assets/right_diag.png");

    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            if (map_[x + y * col] == '-')
            {
                Ground* ground = new Ground(static_cast<float>(tile_size.x * x), static_cast<float>(y * tile_size.y), std::string("Dirt"));
                tileset.push_back(ground);
            }
            else if (map_[x + y * col] == '/')
            {
                Ground* ground = new Ground(static_cast<float>(tile_size.x * x), static_cast<float>(y * tile_size.y), std::string("Left_Diag"));
                tileset.push_back(ground);
            }
            else if (map_[x + y * col] == '\\')
            {
                Ground* ground = new Ground(static_cast<float>(tile_size.x * x), static_cast<float>(y * tile_size.y), std::string("Right_Diag"));
                tileset.push_back(ground);
            }
        }
    }
}
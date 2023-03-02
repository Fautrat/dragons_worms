#include "InGameScene.hpp"
#include <iostream>


InGameScene::InGameScene(Engine& engine) :Scene(engine) , m_manager(EntityManager::getInstance())
{
    if (!backgroundTexture.loadFromFile("assets/Maps/background1.png"))
    {
        std::cout << "Failed to load background" << std::endl;
        return;
    }
    AssetManager::get().loadFont("Shangai", "assets/font/shanghai.ttf");
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
    AssetManager::get().loadTexture("Player", "assets/Dragon/dragon.png");


    player1.getComponent<Transform>()->setTransform(300.f, 0, 0, 0, 0.7f, 0.7f);
    m_manager->addEntity(&player1);
    player1.connectInput(&engine->getInputHandler());

    player2.getComponent<Transform>()->setTransform(1200.f, 0, 0, 0, 0.7f, 0.7f);
    m_manager->addEntity(&player2);

    readMap();
}

void InGameScene::Update(const float& deltaTime)
{
    m_manager->update(deltaTime);

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


    int row = 10, col = 15;

    sf::Vector2f tile_size(1920.f / col, 1080.f / row);
    sf::Vector2f tile_scale(tile_size.x / 220.f, tile_size.y / 220.f);
    AssetManager::get().loadTexture("Dirt", "assets/dirt.png");
    AssetManager::get().loadTexture("Left_Diag", "assets/left_diag.png");
    AssetManager::get().loadTexture("Right_Diag", "assets/right_diag.png");

    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            if (x == 0)
            {
                MapBoundaries* boundariesLeft = new MapBoundaries(-tile_size.x, (float)y * tile_size.y, tile_scale.x, tile_scale.y);
                MapBoundaries* boundariesRight = new MapBoundaries(tile_size.x * col, (float)y * tile_size.y, tile_scale.x, tile_scale.y);
                EntityManager::getInstance()->addEntity(boundariesLeft);
                EntityManager::getInstance()->addEntity(boundariesRight);
            }
            if (map_[x + y * col] == '-')
            {
                Ground* ground = new Ground(tile_size.x * (float)x, (float)y * tile_size.y, tile_scale.x, tile_scale.y, std::string("Dirt"));
                EntityManager::getInstance()->addEntity(ground);
            }
            else if (map_[x + y * col] == '/')
            {
                Ground* ground = new Ground(tile_size.x * (float)x, (float)y * tile_size.y, tile_scale.x, tile_scale.y, std::string("Left_Diag"));
                EntityManager::getInstance()->addEntity(ground);
            }
            else if (map_[x + y * col] == '\\')
            {
                Ground* ground = new Ground(tile_size.x * (float)x, (float)y * tile_size.y, tile_scale.x, tile_scale.y, std::string("Right_Diag"));
                EntityManager::getInstance()->addEntity(ground);
            }
        }
    }
}
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
    m_manager = new EntityManager();

    AssetManager::get().loadTexture("Player", "../../../../assets/Dragon/dragon.png");
    AssetManager::get().loadTexture("Wall", "../../../../assets/Dragon/wall.png");
    AssetManager::get().loadTexture("Circle", "../../../../assets/Dragon/circle.png");
    AssetManager::get().loadTexture("Triangle", "../../../../assets/Dragon/triangle.png");

    dragon.getComponent<Transform>().setTransform(800, 0, 0, 0, 1, 1);
    dragon.addComponent<SpriteRenderer>("Player");
    dragon.addComponent<Rigidbody>(1, false, 0, 2);
    dragon.addComponent<Collider2D>(BOX);
    dragon.addComponent<Input>(&engine->getInputHandler());
    m_manager->addEntity(&dragon);


    circle2.getComponent<Transform>().setTransform(0,300,0,0,0.5f,0.5f);
    circle2.addComponent<SpriteRenderer>("Circle");
    circle2.addComponent<Rigidbody>(1, false, 1, 1);
    circle2.addComponent<Collider2D>(SPHERE);
    m_manager->addEntity(&circle2);

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
        worldptr->addEntityWithPhysics(*entity);
    }

    worldptr->addEntityWithPhysics(circle2);
    worldptr->addEntityWithPhysics(dragon);
}

void InGameScene::Update(const float& deltaTime)
{
    m_manager->refresh();
    m_manager->update(deltaTime);
    worldptr->updatePhysics(deltaTime);
}

void InGameScene::Render(sf::RenderTarget* renderTarget)
{ 
    renderTarget->draw(backgroundSprite);
    m_manager->draw(renderTarget);
}

void InGameScene::readMap(/* std::string& filename */)
{
    char map_50[] = { 
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
            if (map_50[x + y * col] == '-')
            {
                Ground* ground = new Ground(static_cast<float>(tile_size.x * x), static_cast<float>(y * tile_size.y), std::string("Dirt"));
                tileset.push_back(ground);   
            }
            else if (map_50[x + y * col] == '/')
            {
                Ground* ground = new Ground(static_cast<float>(tile_size.x * x), static_cast<float>(y * tile_size.y), std::string("Left_Diag"));
                tileset.push_back(ground);
            }
            else if (map_50[x + y * col] == '\\')
            {
                Ground* ground = new Ground(static_cast<float>(tile_size.x * x), static_cast<float>(y * tile_size.y), std::string("Right_Diag"));
                tileset.push_back(ground);
            }
        }
    }    
}
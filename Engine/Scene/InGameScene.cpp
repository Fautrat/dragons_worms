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
    AssetManager::get().loadTexture("Circle", "../../../../assets/Dragon/Circle.png");
    AssetManager::get().loadTexture("Triangle", "../../../../assets/Dragon/TRIANGLE.png");


    circle2.getComponent<Transform>().setTransform(0,0,0,0,0.5,0.5);
    circle2.addComponent<SpriteRenderer>("Circle");
    circle2.addComponent<Rigidbody>(1, false, 1, 1);
    circle2.addComponent<Collider2D>(SPHERE);
    circle2.addComponent<Input>(&engine->getInputHandler());
    m_manager->addEntity(&circle2);

    Triangle.getComponent<Transform>().setTransform(800, 872, 270, 0, 1, 1);
    Triangle.addComponent<SpriteRenderer>("Triangle");
    Triangle.addComponent<Rigidbody>(1, true, 1, 0);
    Triangle.addComponent<Collider2D>(TRIANGLE);
    m_manager->addEntity(&Triangle);


    ground.getComponent<Transform>().setTransform(1000, 1000, 0, 0, 20, 1);
    ground.addComponent<SpriteRenderer>("Wall");
    ground.addComponent<Rigidbody>(1, true, 0.7, 0);
    ground.addComponent<Collider2D>(BOX);
    m_manager->addEntity(&ground);


    // ADD ENTITY FOR PHYSICS CALCUL IN THE WORLD
    worldptr->addEntityWithPhysics(circle2);
    worldptr->addEntityWithPhysics(Triangle);
    worldptr->addEntityWithPhysics(ground);

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
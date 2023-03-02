#include "InGameScene.hpp"
#include <iostream>


InGameScene::InGameScene(Engine& engine) :Scene(engine) , m_manager(EntityManager::getInstance())
{
    stateScene = EStateScene::RunningScene;
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
    std::shared_ptr<UI> menuManagerUi = std::make_shared<UI>();
    menuManager = new MenuManager(menuManagerUi, *font);
    std::shared_ptr<Menu> InGameMenu = std::make_shared<Menu>("InGameMenu"); // default menu
    menuManager->AddMenu(InGameMenu);
    menuManager->SetCurrentMenu("InGameMenu");

    ui->CreateText("Timer", sf::Color::White, " ", 100, sf::Vector2f(900, 100), *font);
}

InGameScene::~InGameScene()
{
    m_manager->killInstance();
    delete ui;
    delete collision;
    delete menuManager;

}

void InGameScene::Start()
{
    AssetManager::get().loadTexture("Player", "assets/Dragon/dragon.png");


    player1.getComponent<Transform>()->setTransform(300.f, 0, 0, 0, 0.7f, 0.7f);
    m_manager->addEntity(&player1);
    player1.connectInput(&engine->getInputHandler());

    player2.getComponent<Transform>()->setTransform(800.f, 0, 0, 0, 0.7f, 0.7f);
    m_manager->addEntity(&player2);

    readMap();

    for (auto& tile : tileset)
    {
        auto entity = dynamic_cast<Entity*>(tile);
        m_manager->addEntity(entity);

    }
    engine->getInputHandler().connect(EInput::Pause, [&] { PauseScene(); });
}

void InGameScene::Update(const float& deltaTime)
{
    sf::Vector2i mousepos = engine->getMousePos();
    if (menuManager->GetCurrentMenu() != nullptr)
    {
        menuManager->Update(deltaTime, mousepos);
    }

    if(stateScene == EStateScene::RunningScene)
    {
        m_manager->update(deltaTime);
        //worldptr->updatePhysics(deltaTime);

        /* update timer */
        timer -= deltaTime;

        if (timer < 0 || players[currentPlayer]->turnEnding)
            newTurn();

        ui->Text("Timer").setString(std::to_string(static_cast<int>(timer)));
    }
}

void InGameScene::Render(sf::RenderTarget* renderTarget)
{ 
    renderTarget->draw(backgroundSprite);
    m_manager->draw(renderTarget);

    renderTarget->draw(ui->Text("Timer"));
    if (menuManager->GetCurrentMenu() != nullptr) menuManager->Render(renderTarget);
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
    AssetManager::get().loadTexture("Dirt", "assets/dirt.png");
    AssetManager::get().loadTexture("Left_Diag", "assets/left_diag.png");
    AssetManager::get().loadTexture("Right_Diag", "assets/right_diag.png");

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

void InGameScene::PauseScene()
{

    stateScene = EStateScene::PauseScene;

    std::shared_ptr<Menu> PauseMenu = std::make_shared<Menu>("PauseMenu");
    menuManager->AddMenu(PauseMenu);
    menuManager->SetCurrentMenu("PauseMenu");

    // create zone for menu
    // (std::string name, sf::Vector2f position, sf::Vector2f size, sf::Color color, std::function<void(void)> callback);
    float margin = 100.f;
    sf::Vector2<int> resolution = engine->getResolution();
    sf::Vector2f size = sf::Vector2f((float)resolution.x - margin, (float)resolution.y - margin);
    std::cout << "size.x = " << size.x << " size.y = " << size.y << std::endl;
    // orange
    sf::Color orangeColor = sf::Color(169, 134, 104);

    menuManager->AddText("ResumeText", sf::Color::White, "Resume", 100, sf::Vector2f((float)resolution.x / 2, ((float)resolution.y / 2)-300), [&] { ResumeScene(); });
    menuManager->AddText("ExitText", sf::Color::White, "MainMenu", 100, sf::Vector2f((float)resolution.x / 2, ((float)resolution.y / 2)+300), [&] { MainMenu(); });




}

void InGameScene::ResumeScene()
{
    stateScene = EStateScene::RunningScene;
    menuManager->SetCurrentMenu("InGameMenu");
    menuManager->RemoveMenu("PauseMenu");
}

void InGameScene::MainMenu()
{
    engine->setSceneToLoad(MAINMENU);
}
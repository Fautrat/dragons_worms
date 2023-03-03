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
    const auto font = AssetManager::get().getFont("Shangai");

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale({ (float)engine.getRenderWindow().getSize().x / (float)backgroundSprite.getTexture()->getSize().x, (float)engine.getRenderWindow().getSize().y / (float)backgroundSprite.getTexture()->getSize().y});
    ui = new UI();
    collision = new Collision();
    std::shared_ptr<UI> menuManagerUi = std::make_shared<UI>();
    menuManager = new MenuManager(menuManagerUi, *font);
    std::shared_ptr<Menu> InGameMenu = std::make_shared<Menu>("InGameMenu"); // default menu
    menuManager->AddMenu(InGameMenu);
    menuManager->SetCurrentMenu("InGameMenu");

    ui->CreateText("Timer", sf::Color::White, " ", 100, sf::Vector2f((float)engine.getResolution().x / 2.f, 50.f), *font);
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
    player1.getComponent<Transform>()->setTransform(300.f, 500.f, 0, 0, 0.7f, 0.7f);
    player1.initPlayer(FirstTeam);
    player1.connectInput(&engine->getInputHandler());
    player1.startTurn();
    m_manager->addEntity(&player1);

    player2.getComponent<Transform>()->setTransform(1400.f, 500.f, 0, 0, 0.7f, 0.7f);
    player2.initPlayer(SecondTeam);
    m_manager->addEntity(&player2);

    readMap();
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

        for (int i = 0; i <= Player2; i++)
        {
            if (players[i]->getLife() <= 0.f)
                EndingScene(i);
        }

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
    players[currentPlayer]->startTurn();
    timer = 60.f;
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
    AssetManager::get().loadTexture("Dirt", "assets/Maps/dirt.png");
    AssetManager::get().loadTexture("Left_Diag", "assets/Maps/left_diag.png");
    AssetManager::get().loadTexture("Right_Diag", "assets/Maps/right_diag.png");

    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            // set invisible wall around the map left and right
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

void InGameScene::PauseScene()
{

    stateScene = EStateScene::PauseScene;

    std::shared_ptr<Menu> PauseMenu = std::make_shared<Menu>("PauseMenu");
    menuManager->AddMenu(PauseMenu);
    menuManager->SetCurrentMenu("PauseMenu");

    float margin = 100.f;
    sf::Vector2<int> resolution = engine->getResolution();
    sf::Vector2f size = sf::Vector2f((float)resolution.x - margin, (float)resolution.y - margin);
    // orange
    sf::Color orangeColor = sf::Color(169, 134, 104);

    menuManager->AddText("ResumeText", sf::Color::White, "Resume", 100, sf::Vector2f((float)resolution.x / 2, ((float)resolution.y / 2)-300), [&] { ResumeScene(); });
    menuManager->AddText("ExitText", sf::Color::White, "MainMenu", 100, sf::Vector2f((float)resolution.x / 2, ((float)resolution.y / 2)+300), [&] { MainMenu(); });
}

void InGameScene::EndingScene(int winPlayer)
{
    stateScene = EStateScene::PauseScene;

    std::shared_ptr<Menu> EndingMenu = std::make_shared<Menu>("EndingMenu");
    menuManager->AddMenu(EndingMenu);
    menuManager->SetCurrentMenu("EndingMenu");

    float margin = 100.f;
    sf::Vector2<int> resolution = engine->getResolution();
    sf::Vector2f size = sf::Vector2f((float)resolution.x - margin, (float)resolution.y - margin);
    // orange
    sf::Color orangeColor = sf::Color(169, 134, 104);
    std::string txt;
    if (winPlayer == Player1)
        txt = "Player1 has won ! (The red one)";
    else 
        txt = "Player2 has won ! (The yellow one)";
    menuManager->AddText("ResumeText", sf::Color::Red, txt, 100, sf::Vector2f((float)resolution.x / 2.f, ((float)resolution.y + 100.f)), [] {});
    menuManager->AddText("ExitText", sf::Color::Red, "MainMenu", 150, sf::Vector2f((float)resolution.x / 2.f, ((float)resolution.y / 2.f)), [&] { MainMenu(); });
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
#include "Map.hpp"

//std::array<int, 4> Map::GetEmptyAround(int x, int y) const
//{
//    std::array<int, 4> emptyAround = { 0, 0, 0, 0 };
//    if (m_map[x + 1][y] == 0)
//    {
//        emptyAround[0] = 1;
//    }
//    if (m_map[x - 1][y] == 0)
//    {
//        emptyAround[1] = 1;
//    }
//    if (m_map[x][y + 1] == 0)
//    {
//        emptyAround[2] = 1;
//    }
//    if (m_map[x][y - 1] == 0)
//    {
//        emptyAround[3] = 1;
//    }
//    return emptyAround;
//}
//
//void Map::LoadMap()
//{
//    for (int i = 0; i < 50; i++)
//    {
//        for (int j = 0; j < 50; j++)
//        {
//            if (m_map[i][j] == 1)
//            {
//                std::cout << "Wall" << std::endl;
///*
//                Entity wall;
//                AssetManager::get().loadTexture("Wall", "../../../../assets/Dragon/wall.png");
//                wall.addComponent<Transform>(i * 32, j * 32, 1, 1);
//                wall.addComponent<SpriteRenderer>("Wall");
//                wall.addComponent<BoxCollider2D>(
//                        AssetManager::get().getTexture("Wall")->getSize().x * wall.getComponent<SpriteRenderer>().getSprite()->getScale().x,
//                        AssetManager::get().getTexture("Wall")->getSize().y * wall.getComponent<SpriteRenderer>().getSprite()->getScale().y
//                );
//                manager.addEntity(&wall);
//*/
//            }
//            if (m_map[i][j] == 2)
//            {
//                std::cout << "Triangle" << std::endl;
///*
//                Entity Triangle;
//                AssetManager::get().loadTexture("Wall", "../../../../assets/Dragon/TRIANGLE.png");
//                Triangle.addComponent<Transform>(i * 32, j * 32, 1, 1);
//                Triangle.addComponent<SpriteRenderer>("Triangle");
//                Triangle.addComponent<TriangleCollider2D>(
//                        AssetManager::get().getTexture("Triangle")->getSize().x * Triangle.getComponent<SpriteRenderer>().getSprite()->getScale().x, DOWNRIGHT
//                );
//                manager->addEntity(&triangle);
//*/
//
//            }
//        }
//    }
//}
#pragma once
#include "../ECS/Entity.h"
#include <stdlib.h>     /* srand, rand */


enum ETiles
{
    EMPTY = 0,
    WALL = 1,
    TRIANGLE = 2,
};

class Map
{
public:
    Map() {
        // fill array with temp map
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 51; j++)
            {
                m_tiles[i][j] = 0;
            }
        }
        std::cout << "Map created" << std::endl;

        RandomFloorHeight();
        // print map
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 51; j++)
            {
                std::cout << m_tiles[i][j] << ",";
            }
            std::cout << std::endl;
        }
    }
    virtual ~Map() {
        //delete m_tiles;
    }

    void RandomFloorHeight() {
        int temp[11] ={0,0,0,0,0,0,0,0,0,0,0};
        int height = 0;
        for(int i = 0; i < 11; i++) {
            height = rand() % 3 + 2;
            temp[i] = height;
        }
        // print temp
        std::cout << "temp" << std::endl;
        for (int i = 0; i < 10; i++)
        {
            std::cout << temp[i] << ",";
        }
        std::cout << std::endl;

        int tile_x = 0;
        int tile_y = 0;
        int loop = 0;
        for(int i = 0; i < 11; i++) {
            tile_x = temp[i]+3;
            tile_y = (51 / 10) * i;
            m_tiles[tile_x][tile_y] = 1;
            // fill 1 tile under
            if (temp[i] == temp[i+1]) {
                loop = 1;
            }
            for (int k = tile_x; k < 10; k++) {
                m_tiles[k][tile_y] = 1;
            }
        }
    }

private:
    int m_tiles[10][51];
};


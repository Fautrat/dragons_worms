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
        for (int i = 0; i < m_width; i++)
        {
            for (int j = 0; j < m_height; j++)
            {
                m_tiles[i][j] = ' ';
            }
        }
        std::cout << "Map created" << std::endl;

        RandomFloorHeight();
        // print map
        for (int i = 0; i < m_width; i++)
        {
            for (int j = 0; j < m_height; j++)
            {
                std::cout << m_tiles[i][j] << ",";
            }
            std::cout << std::endl;
        }
    }
    virtual ~Map() {
        //delete m_tiles;
    }

    void RandomFloorHeight(int heightMin=-1, int heightMax=1) {
        int height = 15;
        int prevHeight = 15;
        for (int j = 0; j < m_width; j++)
        {
            // random height between (height + min) and (height + max)
            height += rand() % (heightMax - heightMin + 1) + heightMin;
            if (height < 0)
                height = 0;
            if (height > m_height-1)
                height = m_height-1;
            if (height > prevHeight)
            {
                m_tiles[height][j] = '\\';
            }
            else if (height < prevHeight)
            {
                m_tiles[height][j] = '/';
            }
            else
            {
                m_tiles[height][j] = '-';
            }
            // fill in the rest of the floor
            for (int i = height + 1; i < m_height; i++)
            {
                m_tiles[i][j] = '-';
            }
            prevHeight = height;
        }
    }

private:
    char m_tiles[30][30];
    int m_width = 30;
    int m_height = 30;
};


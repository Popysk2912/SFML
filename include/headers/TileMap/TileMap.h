#pragma once
#include "headers/Engine/Program.h"
#include <fstream>

class TileMap
{
public:
    TileMap() { sizeX = 0; sizeY = 0; tileSize = 0; }
    TileMap(int s_x, int s_y, float tileSize);
    std::vector<std::vector<Sprite*>> loadFromVector(std::vector<std::vector<int>> vec);
    void Draw(SpriteRenderer& renderer);
private:
    int sizeX, sizeY;
    float tileSize;
    std::vector<std::vector<Sprite*>> tiles;
};
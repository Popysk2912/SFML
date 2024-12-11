#include "headers/TileMap/TileMap.h"
#include <iostream>
#include <fstream>
#include <sstream>

TileMap::TileMap(int s_x, int s_y, float tileSize)
{
    sizeX = s_x;
    sizeY = s_y;
    this->tileSize = tileSize;
    tiles.resize(sizeY);
    for (auto& t : tiles)
    {
        t.resize(sizeX);
    }
}

std::vector<std::vector<Sprite*>> TileMap::loadFromVector(std::vector<std::vector<int>> vec)
{
    std::vector<Texture2D> textures = ResourceManager::GetTileTextures();
    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
        {
            Sprite* sprite = new Sprite();
            sprite->setTexture(textures[vec[i][j]]);
            sprite->setPosition(glm::vec2(i * tileSize, j * tileSize));
            sprite->setSize(glm::vec2(tileSize, tileSize));
            sprite->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
            tiles[i][j] = sprite;
        }
    }
    return tiles;
}

void TileMap::Draw(SpriteRenderer& renderer)
{
    for (const auto& row : tiles)
    {
        for (const auto& tile : row)
        {
            tile->draw(renderer); 
        }
    }
}

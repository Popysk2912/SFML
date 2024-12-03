#include "Program.h"

class Game : public Program
{
public:
    Game(int width, int height) : Program(width, height) { loadResources(); }
private:
    std::vector<Sprite*> sprites;
    glm::vec2 sprite_size = glm::vec2(32.0f, 32.0f);
    int size = 3;
    glm::vec2 pos = glm::vec2(8, 8);
    glm::vec2 dir = glm::vec2(0, 0);

    void init() override
    {
        for(int i = 0; i <= size; i++)
        {
            Sprite* sprite = new Sprite(ResourceManager::GetTexture("segment"), pos * sprite_size, sprite_size, 0, glm::vec3(1.0f, 1.0f, 1.0f));
            sprites.push_back(sprite);
        }
        effects->Shake = true;
    }
    void update() override
    {
        for (int i = sprites.size()-1; i >= 0; i--)
        {
            if(i != 0)
            {
                sprites[i]->setPosition(sprites[i - 1]->getPosition());
            }
        }
        sprites[0]->setPosition(sprites[0]->getPosition() + (dir * sprite_size));
    }
    void input(sf::Event e) override
    {
        if (e.type == sf::Event::KeyPressed)
        {
            // Обработка нажатия клавиш стрелок
            if (e.key.code == sf::Keyboard::Up)
            {
                dir = glm::vec2(0, -1);
            }
            else if (e.key.code == sf::Keyboard::Down)
            {
                dir = glm::vec2(0, 1);
            }
            else if (e.key.code == sf::Keyboard::Left)
            {
                dir = glm::vec2(-1, 0);
            }
            else if (e.key.code == sf::Keyboard::Right)
            {
                dir = glm::vec2(1, 0);
            }
        }
    }

    void render() override
    {
        for(auto sprite : sprites)
        {
            Draw(*sprite);
        }
    }
    void loadResources() override
    {
        ResourceManager::LoadTexture("segment.png", true, "segment");
    }
};
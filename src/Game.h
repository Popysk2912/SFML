#include "Program.h"
#include <unordered_map>

class Player : public Sprite
{
public:
    Player(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color) : Sprite(texture, position, size, rotate, color) {}
    void move(float x, float y)
    {
        position.x += x;
        position.y += y;
    }
};

class Game : public Program
{
public:
    Game(int width, int height) : Program(width, height) { loadResources(); }
private:
    Player* player;
    glm::vec2 sprite_size = glm::vec2(32.0f, 32.0f);
    glm::vec2 pos = glm::vec2(0, 0);
    glm::vec2 dir = glm::vec2(0, 0);
    glm::vec2 velocity = glm::vec2(0, 0);
    float speed = 250.0f;

    void init() override
    {
        player = new Player(ResourceManager::GetTexture("segment"), pos * sprite_size, sprite_size, 0, glm::vec3(1.0f, 1.0f, 1.0f));
        effects->Shake = false;
    }
    void update(float dt) override
    {
        if(InputManager::isKeyDown(sf::Keyboard::Up))
        {
            velocity.y = 1;
        }
        else if(InputManager::isKeyDown(sf::Keyboard::Down))
        {
            velocity.y = -1;
        }
        else
        {
            velocity.y = 0;
        }

        if (InputManager::isKeyDown(sf::Keyboard::Right))
        {
            velocity.x = 1;
        }
        else if (InputManager::isKeyDown(sf::Keyboard::Left))
        {
            velocity.x = -1;
        }
        else
        {
            velocity.x = 0;
        }
        glm::normalize(velocity);
        player->move(velocity.x * speed * dt, velocity.y * speed * dt);
    }
    void render() override
    {
        Draw(*player);
    }
    void loadResources() override
    {
        ResourceManager::LoadTexture("segment.png", true, "segment");
    }
};
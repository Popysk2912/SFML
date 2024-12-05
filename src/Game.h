#ifndef GAME_H
#define GAME_H

#include "Program.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include <glm/glm.hpp>

class Game : public Program
{
public:
    Game(int width, int height);
private:
    Player* player;
    glm::vec2 pos;
    glm::vec2 velocity;
    float speed;

    void init() override;
    void update(float dt) override;
    void render() override;
    void loadResources() override;
};

#endif // GAME_H

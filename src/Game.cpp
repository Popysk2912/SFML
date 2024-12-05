#include "Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define sprite_size glm::vec2(32.0f, 32.0f)

Game::Game(int width, int height) : Program(width, height)
{
    pos = glm::vec2(0, 0);
    speed = 128.0f;
    loadResources();
}

void Game::init()
{
    player = new Player(ResourceManager::GetTexture("segment"), pos, sprite_size, 0, glm::vec3(1.0f, 1.0f, 1.0f), true);
}

void Game::update(float dt)
{
    velocity.y = InputManager::getAxis("vertical");
    velocity.x = InputManager::getAxis("horizontal");
    if (velocity != glm::vec2(0.0f, 0.0f))
        velocity = glm::normalize(velocity);
    player->move(velocity.x * speed * dt, velocity.y * speed * dt);
}

void Game::render()
{
    Draw(*player);
}

void Game::loadResources()
{
    InputManager::createAxis(sf::Keyboard::Down, sf::Keyboard::Up, "vertical");
    InputManager::createAxis(sf::Keyboard::Left, sf::Keyboard::Right, "horizontal");
    ResourceManager::LoadTexture("segment.png", true, "segment");
}

#pragma once
#include "headers/Engine/SpriteRenderer.h"
#include "headers/Engine/Sprite.h"
#include "headers/Engine/shader.h"
#include "headers/Engine/post_processor.h"
#include "headers/Managers/ResourceManager.h"
#include "headers/Managers/InputManager.h"

class Program
{
public:
    Program(int width, int height); 
    virtual ~Program() = default;
    void run();

private:
    bool running = true;
    Shader shader;
    Shader pps;
    sf::RenderWindow window;

protected:
    int width, height; 
    sf::Clock clock;
    float time = 0;

    std::unique_ptr<SpriteRenderer> spriteRenderer;
    std::unique_ptr<PostProcessor> effects;

    virtual void loadResources();
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    void setFrameRate(int frameRate);
    void Draw(Sprite sprite);
};

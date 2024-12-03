#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include "SpriteRenderer.h"
#include "Sprite.h"
#include "shader.h"
#include "post_processor.h"
#include "ResourceManager.h"

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

    std::unique_ptr <SpriteRenderer> spriteRenderer;
    std::unique_ptr<PostProcessor> effects;

    virtual void loadResources();
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    void Draw(Sprite sprite);
};

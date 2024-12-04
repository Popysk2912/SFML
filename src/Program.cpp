#include "Program.h"

Program::Program(int width, int height)
{
    this->width = width; 
    this->height = height;
    window.create(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, sf::ContextSettings(16));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction))) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    this->loadResources();
    shader = ResourceManager::GetShader("sprite");
    pps = ResourceManager::GetShader("effects");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    shader.SetMatrix4("projection", projection, true);

    spriteRenderer = std::make_unique<SpriteRenderer>(shader);
    effects = std::make_unique<PostProcessor>(pps, width, height);
}

void Program::loadResources()
{
    ResourceManager::Init();
    ResourceManager::LoadShader("default.vert", "default.frag", nullptr, "sprite");
    ResourceManager::LoadShader("effects.vert", "effects.frag", nullptr, "effects");
    ResourceManager::LoadTexture("texture.png", true, "sprite");
}

void Program::Draw(Sprite sprite)
{
    sprite.draw(*spriteRenderer);
}

void Program::run()
{
    init();
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            InputManager::updateKeys(event);
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        float dt = clock.restart().asSeconds();
        time = clock.getElapsedTime().asMilliseconds();
        this->update(dt);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        effects->BeginRender();
        this->render();
        effects->EndRender();
        effects->Render(time);
        window.display();
    }
}

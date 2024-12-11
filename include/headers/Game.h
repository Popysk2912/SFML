#pragma once
#include "headers/Engine/Program.h"

class Game : public Program
{
private:
	void init() override;
	void loadResources() override;
	void update(float dt) override;
	void render() override;
public:
	Game(int width, int height) : Program(width, height) {  };
	~Game() = default;
};
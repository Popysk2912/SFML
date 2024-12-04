#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>


class InputManager
{
private:
	static std::unordered_map<int, bool> keys;
public:
	static void updateKeys(sf::Event e);
	static bool isKeyDown(int keyCode);
};
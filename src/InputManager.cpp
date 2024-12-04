#include "InputManager.h"

std::unordered_map<int, bool> InputManager::keys;

void InputManager::updateKeys(sf::Event e)
{
    if (e.type == sf::Event::EventType::KeyPressed) {
        if (keys.count(e.key.code) == 0) {
            keys[e.key.code] = true;
        }
    }
    if (e.type == sf::Event::EventType::KeyReleased) {
        if (keys.count(e.key.code) == 1) {
            keys.erase(e.key.code);
        }
    }
}

bool InputManager::isKeyDown(int keyCode)
{
    return (keys.count(keyCode) == 1);
}

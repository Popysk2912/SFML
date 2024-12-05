#include "GameObject.h"

void GameObject::move(float x, float y)
{
	this->position.x += x;
	this->position.y += y;
}

void GameObject::enableCollision()
{
	this->collision = true;
}

void GameObject::disableCollision()
{
	this->collision = false;
}

bool GameObject::checkCollision(GameObject* other)
{
    if (!collision)
        return false;
    float leftA = this->position.x;
    float rightA = this->position.x + this->size.x;
    float topA = this->position.y;
    float bottomA = this->position.y + this->size.y;

    float leftB = other->position.x;
    float rightB = other->position.x + other->size.x;
    float topB = other->position.y;
    float bottomB = other->position.y + other->size.y;

    if (bottomA <= topB ||  
        topA >= bottomB ||  
        rightA <= leftB ||  
        leftA >= rightB)    
    {
        return false;
    }
    return true;
}

#include "Program.h"

class GameObject : public Sprite
{
private:
    bool collision;
public:
    GameObject(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, bool collidable) : Sprite(texture, position, size, rotate, color), collision(collidable) {}
    void move(float x, float y);
    void enableCollision();
    void disableCollision();
    bool checkCollision(GameObject* other);
};

class Player : public GameObject
{
public:
    Player(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, bool collidable) : GameObject(texture, position, size, rotate, color, collidable) {}
    
};
#include "headers/Engine/Sprite.h"

Sprite::Sprite(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color) :
texture(texture), position(position), size(size), rotate(rotate), color(color)
{
}

void Sprite::draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(texture, position, size, rotate, color);
}

void Sprite::printProperties()
{
    std::cout << "GameObject Properties:" << std::endl;

    // ������� �������� ������� (�������������� �� ������ Sprite)
    std::cout << "Texture: " << texture.ID << std::endl;
    std::cout << "Position: (" << position.x << ", " << position.y << ")" << std::endl;
    std::cout << "Size: (" << size.x << ", " << size.y << ")" << std::endl;
    std::cout << "Rotation: " << rotate << " degrees" << std::endl;
    std::cout << "Color: (" << color.r << ", " << color.g << ", " << color.b << ")" << std::endl;

}

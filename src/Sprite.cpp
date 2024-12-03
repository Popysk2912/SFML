#include "Sprite.h"

Sprite::Sprite(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color) :
texture(texture), position(position), size(size), rotate(rotate), color(color)
{
}

void Sprite::draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(texture, position, size, rotate, color);
}

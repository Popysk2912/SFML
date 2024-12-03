#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SpriteRenderer.h"
#include "texture.h"

class Sprite
{
public:
	Sprite(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color);
	void draw(SpriteRenderer& renderer);
	
protected:
	Texture2D texture;
	glm::vec2 position;
	glm::vec2 size;
	GLfloat rotate;
	glm::vec3 color;
};
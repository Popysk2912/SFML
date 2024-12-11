#pragma once
#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SpriteRenderer.h"
#include "texture.h"

class Sprite
{
public:
	Sprite(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color);
    Sprite() : texture(Texture2D()), position(glm::vec2(0, 0)), size(glm::vec2(0, 0)), rotate(0), color(glm::vec3(0, 0, 0)) { }
	void draw(SpriteRenderer& renderer);

    Texture2D getTexture() const { return texture; }
    glm::vec2 getPosition() const { return position; }
    glm::vec2 getSize() const { return size; }
    GLfloat getRotate() const { return rotate; }
    glm::vec3 getColor() const { return color; }

    void setTexture(const Texture2D& texture) { this->texture = texture; }
    void setPosition(const glm::vec2& position) { this->position = position; }
    void setSize(const glm::vec2& size) { this->size = size; }
    void setRotate(GLfloat rotate) { this->rotate = rotate; }
    void setColor(const glm::vec3& color) { this->color = color; }
    void printProperties();

	
protected:
	Texture2D texture;
	glm::vec2 position;
	glm::vec2 size;
	GLfloat rotate;
	glm::vec3 color;
};
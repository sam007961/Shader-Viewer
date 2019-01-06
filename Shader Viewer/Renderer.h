#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Geometry.h"
#include "Texture.h"

class Renderer {
private:
	GLProgram* program;
	unsigned int n_elements;

public:
	Renderer() : program(nullptr) {}

	void setProgram(GLProgram* program) { // set program
		assert(program != nullptr);
		assert((*program) > 0);

		this->program = program;
	}

	template<class GeometryType>
	void draw(const GeometryType& target, GLenum mode=GL_TRIANGLES) const { // draw geometry
		assert(program != nullptr);
		assert((*program) > 0);

		glUseProgram(*program);
		glBindVertexArray(target);
		glDrawElements(mode, target.elementCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	template<class GeometryType>
	void draw(const GeometryType& target, const GLTexture& texture, GLenum mode = GL_TRIANGLES) const { // draw geometry to texture
		assert(program != nullptr);
		assert((*program) > 0);

		glUseProgram(*program);
		glBindVertexArray(target);
		glDrawElements(mode, target.elementCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
};
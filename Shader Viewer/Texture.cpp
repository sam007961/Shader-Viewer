#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>

#include "Texture.h"

GLTexture::GLTexture() { glGenTextures(1, &handle); }
GLTexture::~GLTexture() { glDeleteTextures(1, &handle); }

void GLTexture::loadData(GLuint format, const char* path) {
	// load data
	int width, height, nChannels;
	byte* data = stbi_load(path, &width, &height, &nChannels, 0);
	if(!data) throw std::runtime_error("Failed to load texture.");

	// setup texture
	setup(format, data, width, height, nChannels);

	// free data
	stbi_image_free(data);
}

void GLTexture2D::setup(GLuint format, byte* data, int width, int height, int nChannels) {
	// bind
	glBindTexture(GL_TEXTURE_2D, handle);

	// default parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load texture
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}
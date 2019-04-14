#pragma once

#include <map>
#include <string>
#include <GL/glew.h>
#include "Utils\ReferenceCounter.h"

class TextureData : public ReferenceCounter
{

	GLuint* m_textureID;
	GLenum m_textureTarget;
	int m_numTextures;
	int m_width;
	int m_height;

public:

	TextureData(GLenum textureTarget, int width, int height, int numTextures, unsigned char** data, GLfloat* filters);
	virtual ~TextureData();

	void Bind(int textureNum);

private:

	void InitTextures(unsigned char** data, GLfloat* filters);

};

class Texture
{

	static std::map<std::string, TextureData*> s_resourceMap;

	TextureData* m_textureData;
	std::string m_fileName;

public:
	Texture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
	Texture(int width = 0, int height = 0, unsigned char* data = 0, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);
	virtual ~Texture();

	void Bind(unsigned int unit = 0) const;
	void BindAsRenderTarget();

};


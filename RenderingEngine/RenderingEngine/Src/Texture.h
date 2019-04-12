#pragma once

#include <map>
#include <string>
#include <GL/glew.h>
#include "Utils\ReferenceCounter.h"

class TextureData : public ReferenceCounter
{

	GLenum m_textureTarget;
	GLuint m_textureID;

public:

	TextureData(GLenum textureTarget);
	virtual ~TextureData();

	inline GLenum GetTextureTarget() { return m_textureTarget; }
	inline GLuint GetTextureID() { return m_textureID; }

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

private:

	void InitTexture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter);

};


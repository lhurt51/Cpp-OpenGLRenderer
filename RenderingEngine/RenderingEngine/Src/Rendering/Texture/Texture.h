#pragma once

#include <map>
#include <string>
#include <GL/glew.h>

#include "../../Core/Utils/AssetManager/ReferenceCounter.h"

class TextureData : public ReferenceCounter
{

	GLuint* m_textureID;
	GLenum m_textureTarget;
	GLuint m_frameBuffer;
	GLuint m_renderBuffer;
	int m_numTextures;
	int m_width;
	int m_height;

public:

	TextureData(GLenum textureTarget, int width, int height, int numTextures, unsigned char** data, GLfloat* filters, GLenum* internalFormat, GLenum* format, bool clamp, GLenum* attachments);
	virtual ~TextureData();

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

	void Bind(int textureNum) const;
	void BindAsRenderTarget() const;

private:

	void InitTextures(unsigned char** data, GLfloat* filters, GLenum* internalFormat, GLenum* format, bool clamp);
	void InitRenderTarget(GLenum* attachments);

};

class Texture
{

	static std::map<std::string, TextureData*> s_resourceMap;

	TextureData* m_textureData;
	std::string m_fileName;

public:
	Texture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR_MIPMAP_LINEAR, GLenum internalFormat = GL_RGBA, GLenum format = GL_RGBA, bool clamp = false, GLenum attachment = GL_NONE);
	Texture(int width = 0, int height = 0, unsigned char* data = 0, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR_MIPMAP_LINEAR, GLenum internalFormat = GL_RGBA, GLenum format = GL_RGBA, bool clamp = false, GLenum attachment = GL_NONE);
	Texture(const Texture& texture);
	virtual ~Texture();

	inline int GetWidth() const { return m_textureData->GetWidth(); }
	inline int GetHeight() const { return m_textureData->GetHeight(); }

	void Bind(unsigned int unit = 0) const;
	void BindAsRenderTarget() const;

	void operator=(Texture texture);
	bool operator==(const Texture& texture) const { return m_textureData == texture.m_textureData; }
	bool operator!=(const Texture& texture) const { return !operator==(texture); }

};


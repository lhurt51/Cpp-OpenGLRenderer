#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{

	GLuint m_texture;

public:
	Texture(const std::string& fileName);
	virtual ~Texture();

	void Bind(unsigned int unit);

};


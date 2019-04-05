#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{

	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];

public:

	Shader(const std::string& fileName);
	virtual ~Shader();

	// Bind the vertex and fragment shaders
	void Bind(void);

};


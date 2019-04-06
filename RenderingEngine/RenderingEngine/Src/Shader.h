#pragma once

#include <string>
#include <GL/glew.h>

class Transform;
class Camera;

class Shader
{
	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

public:

	Shader(const std::string& fileName);
	virtual ~Shader();

	// Bind the vertex and fragment shaders
	void Bind(void);
	void Update(const Transform& transform, const Camera& camera);

};


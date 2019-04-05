#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{
private:

	glm::vec3 pos;

protected:

public:

	Vertex(const glm::vec3& pos)
	{
		this->pos = pos;
	}
};

class Mesh
{

	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

public:

	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();

	void Draw();

};


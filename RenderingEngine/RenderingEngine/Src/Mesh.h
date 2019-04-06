#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "ObjLoader/obj_loader.h"

class Vertex
{
private:

	glm::vec3 pos;
	glm::vec2 texCoord;

protected:

public:

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
};

class Mesh
{

	enum
	{
		POSITION_VB,
		TEXTCOORD_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

public:

	Mesh(const std::string& fileName);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	virtual ~Mesh();

	void Draw();

private:

	void InitMesh(const IndexedModel& model);

};


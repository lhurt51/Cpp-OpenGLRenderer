#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "ObjLoader/obj_loader.h"

class Vertex
{
private:

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

protected:

public:

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }
};

class Mesh
{

	enum
	{
		POSITION_VB,
		TEXTCOORD_VB,
		NORMAL_VB,
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


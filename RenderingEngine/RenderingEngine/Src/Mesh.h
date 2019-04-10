#pragma once

#include <map>
#include "Mesh\Vertex.h"
#include "Utils\ReferenceCounter.h"

class MeshData : public ReferenceCounter
{

	unsigned int m_vbo;
	unsigned int m_ibo;
	int m_size;

public:

	MeshData(int indexSize);
	virtual ~MeshData();

	inline unsigned int GetVBO() { return m_vbo; }
	inline unsigned int GetIBO() { return m_ibo; }
	inline unsigned int GetSize() { return m_size; }

};

class Mesh
{

	static std::map<std::string, MeshData*> s_resourceMap;
	std::string m_fileName;
	MeshData* m_meshData;

public:

	Mesh(const std::string& fileName);
	Mesh(Vertex* vertices, int vertSize, int* indices, unsigned int indexSize, bool calcNormals);
	virtual ~Mesh();

	void Draw();

private:

	void CalcNormals(Vertex* vertices, int vertSize, int* indices, int indexSize);
	void InitMesh(Vertex* vertices, int vertSize, int* indices, int indexSize, bool calcNormals = true);

};


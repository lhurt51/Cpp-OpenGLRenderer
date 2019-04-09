#pragma once

#include "../GameComponent.h"
#include "../Mesh.h"

class MeshRenderer : public GameComponent
{

	Mesh* m_mesh;
	Material* m_material;

public:

	MeshRenderer(Mesh* mesh, Material* material)
	{
		m_mesh = mesh;
		m_material = material;
	}

	virtual ~MeshRenderer()
	{
		if (m_mesh) delete m_mesh;
		if (m_material) delete m_material;
	}

	virtual void Render(Shader* shader, RenderingEngine* renderingEngine)
	{
		shader->Bind();
		shader->UpdateUniforms(GetTransform(), *m_material, renderingEngine);
		m_mesh->Draw();
	}
};

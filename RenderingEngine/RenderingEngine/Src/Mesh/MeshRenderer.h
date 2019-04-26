#pragma once

#include "../GameComponent.h"
#include "../Mesh/Mesh.h"

class MeshRenderer : public GameComponent
{

	Mesh		m_mesh;
	Material	m_material;

public:

	MeshRenderer(const Mesh& mesh, const Material& material) : m_mesh(mesh), m_material(material)
	{}

	virtual void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
	{
		shader.Bind();
		shader.UpdateUniforms(GetTransform(), m_material, renderingEngine, camera);
		m_mesh.Draw();
	}
};

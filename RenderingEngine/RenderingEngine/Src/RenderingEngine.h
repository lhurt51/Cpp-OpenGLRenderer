#pragma once

#include "Camera.h"
#include "Lighting/Lighting.h"
#include "Material.h"

#include <vector>
#include <map>

class Transform;
class Shader;
class GameObject;

class RenderingEngine
{

	Camera* m_mainCamera;
	BaseLight* m_activeLight;
	Shader* m_defaultShader;
	std::vector<BaseLight*> m_lights;
	std::map<std::string, unsigned int> m_samplerMap;

public:

	RenderingEngine();
	virtual ~RenderingEngine();

	void Render(GameObject* object);

	inline Camera& GetMainCamera() { return *m_mainCamera; }
	inline BaseLight* GetActiveLight() { return m_activeLight; }

	inline void AddLight(BaseLight* light) { m_lights.push_back(light); }
	inline void AddCamera(Camera* camera) { m_mainCamera = camera; }

	inline unsigned int GetSamplerSlot(const std::string& samplerName) { return m_samplerMap[samplerName]; }

	virtual void UpdateUniformStruct(const Transform& transform, const Material& material, Shader* shader, const std::string& uniformName, const std::string& uniformType)
	{
		throw uniformType + " is not supported by the rendering engine";
	}

};


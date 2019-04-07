#pragma once

#include "Camera.h"
// #include "Lighting.h"
// #include "MappedValues.h"
// #include "Material.h"

#include <vector>
#include <map>

// class GameObject;

class RenderingEngine
{

	Camera* m_mainCamera;
	// BaseLight* m_activeLight;
	// Shader* m_defaultShader;
	// std::vector<BaseLight*> m_lights;
	// std::map<std::string, unsigned int> m_samplerMap;

public:
	RenderingEngine();
	virtual ~RenderingEngine();
};


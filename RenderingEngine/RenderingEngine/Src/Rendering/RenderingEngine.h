#pragma once

#include <vector>
#include <map>

#include "Camera/Camera.h"
#include "Lighting/Lighting.h"
#include "Material/Material.h"
#include "Mesh/Mesh.h"
#include "Window/Window.h"
#include "../Core/Utils/AssetManager/MappedValues.h"
#include "../Core/Utils/Time/Profiling.h"

class GameObject;

class RenderingEngine : public MappedValues
{

	static const Matrix4f BIAS_MATRIX;
	static const int NUM_SHADOWS_MAPS = 10;

	ProfileTimer					m_renderProfileTimer;
	ProfileTimer					m_windowSyncProfileTimer;

	Transform						m_planeTransform;
	Mesh							m_plane;

	const Window*					m_window;
	Texture							m_tempTarget;
	Material						m_planeMaterial;
	Texture							m_shadowMaps[NUM_SHADOWS_MAPS];
	Texture							m_shadowTempTargets[NUM_SHADOWS_MAPS];

	Shader							m_defaultShader;
	Shader							m_shadowMapShader;
	Shader							m_nullFilter;
	Shader							m_gausBlurFilter;
	Shader							m_fxaaFilter;
	Matrix4f						m_lightMatrix;
	
	Transform						m_altCameraTransform;
	Camera							m_altCamera;
	const Camera*					m_mainCamera;

	const BaseLight*				m_activeLight;
	std::vector<const BaseLight*>	m_lights;

	std::map<std::string, unsigned int> m_samplerMap;

public:

	RenderingEngine(const Window& window);
	virtual ~RenderingEngine()
	{}

	void Render(const GameObject& object);

	inline void AddLight(const BaseLight& light) { m_lights.push_back(&light); }
	inline void SetMainCamera(const Camera& camera) { m_mainCamera = &camera; }

	inline const BaseLight& GetActiveLight() const { return *m_activeLight; }
	inline unsigned int GetSamplerSlot(const std::string& samplerName) const { return m_samplerMap.find(samplerName)->second; }
	inline const Matrix4f& GetLightMatrix() const { return m_lightMatrix; }

	virtual void UpdateUniformStruct(const Transform& transform, const Material& material, const Shader& shader, const std::string& uniformName, const std::string& uniformType) const
	{
		throw uniformType + " is not supported by the rendering engine";
	}

	inline double DisplayRenderTime(double dividend) { return m_renderProfileTimer.DisplayAndReset("Render Time: ", dividend); }
	inline double DisplayWindowSyncTime(double dividend) { return m_windowSyncProfileTimer.DisplayAndReset("Window Sync Time: ", dividend); }

protected:

	inline void SetSamplerSlot(const std::string& name, unsigned int value) { m_samplerMap[name] = value; }

private:

	void BlurShadowMap(int shadowMapIndex, float blurAmount);
	void ApplyFilter(const Shader& filter, const Texture& source, const Texture* dest);

};


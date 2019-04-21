#pragma once

#include "../Utils/Math/MathUtils.h"
#include "../GameComponent.h"

class CoreEngine;

class ShadowInfo
{

	Matrix4f m_projection;
	bool m_flipFaces;
	float m_shadowSoftness;
	float m_lightBleedReduction;
	float m_varianceMin;

public:

	ShadowInfo(const Matrix4f& projection, bool flipFaces, float shadowSoftness = 1.0f, float lightBleedReduction = 0.2f, float minVariance = 0.00002f) :
		m_projection(projection),
		m_flipFaces(flipFaces),
		m_shadowSoftness(shadowSoftness),
		m_lightBleedReduction(lightBleedReduction),
		m_varianceMin(minVariance)
	{}

	inline const Matrix4f& GetProjection() const { return m_projection; }
	inline bool GetFlipFaces() const { return m_flipFaces; }
	inline float GetShadowSoftness() const { return m_shadowSoftness; }
	inline float GetLightBleedReduction() const { return m_lightBleedReduction; }
	inline float GetMinVariance() const { return m_varianceMin; }

};

class BaseLight : public GameComponent
{

	Shader* m_shader;
	ShadowInfo* m_shadowInfo;

public:

	Vector3f color;
	float intensity;

	BaseLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0) : m_shader(0), m_shadowInfo(0), color(color), intensity(intensity)
	{}

	virtual ~BaseLight();

	virtual void AddToEngine(CoreEngine* engine);
	inline Shader* GetShader() const { return m_shader; }
	inline ShadowInfo* GetShadowInfo() const { return m_shadowInfo;  }

protected:

	void SetShader(Shader* shader);
	void SetShadowInfo(ShadowInfo* shadowInfo);

};

struct DirectionalLight : public BaseLight
{
	DirectionalLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0);
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;

	Attenuation(float constant = 0, float linear = 0, float exponent = 1.0f) : constant(constant), linear(linear), exponent(exponent)
	{}
};

struct PointLight : public BaseLight
{
	Attenuation atten;
	float range;

	PointLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation());
};

struct SpotLight : public PointLight
{
	float cutoff;

	SpotLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float viewAngle = ToRadians(179.0f), int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReduction = 0.2f, float minVariance = 0.00002f);
};

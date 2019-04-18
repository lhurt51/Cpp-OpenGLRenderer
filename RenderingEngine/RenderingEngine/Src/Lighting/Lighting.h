#pragma once

#include "../Utils/Math/MathUtils.h"
#include "../GameComponent.h"

class CoreEngine;

class ShadowInfo
{

	Matrix4f m_projection;
	float m_bias;
	bool m_flipFaces;

public:

	ShadowInfo(const Matrix4f& projection, float bias, bool flipFaces) : m_projection(projection), m_bias(bias), m_flipFaces(flipFaces)
	{}

	inline Matrix4f GetProjection() const { return m_projection; }
	inline float GetBias() const { return m_bias; }
	inline bool GetFlipFaces() const { return m_flipFaces; }

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

	SpotLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float cutoff = 0);
};

#pragma once

#include "../Utils/Math/MathUtils.h"
#include "../GameComponent.h"

class CoreEngine;

class BaseLight : public GameComponent
{

	Shader* m_shader;

public:

	Vector3f color;
	float intensity;

	BaseLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0) : m_shader(0), color(color), intensity(intensity)
	{}

	virtual ~BaseLight();

	virtual void AddToEngine(CoreEngine* engine);
	inline Shader* GetShader() { return m_shader; }

	void SetShader(Shader* shader);
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

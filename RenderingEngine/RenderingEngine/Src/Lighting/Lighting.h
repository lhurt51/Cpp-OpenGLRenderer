#pragma once

#include "../Utils/Math/MathUtils.h"
#include "../GameComponent.h"

class CoreEngine;

struct ShadowCameraTransform
{
	Vector3f pos;
	Quaternion rot;
};

class ShadowInfo
{

	Matrix4f m_projection;
	bool m_flipFaces;
	int m_shadowMapSizeAsPowerOf2;
	float m_shadowSoftness;
	float m_lightBleedReduction;
	float m_varianceMin;

public:

	ShadowInfo(const Matrix4f& projection, bool flipFaces, int shadowMapSizeAsPowerOf2, float shadowSoftness = 1.0f, float lightBleedReduction = 0.2f, float minVariance = 0.00002f) :
		m_projection(projection),
		m_flipFaces(flipFaces),
		m_shadowMapSizeAsPowerOf2(shadowMapSizeAsPowerOf2),
		m_shadowSoftness(shadowSoftness),
		m_lightBleedReduction(lightBleedReduction),
		m_varianceMin(minVariance)
	{}

	inline const Matrix4f& GetProjection() const { return m_projection; }
	inline bool GetFlipFaces() const { return m_flipFaces; }
	inline int GetShadowMapSizeAsPowerOf2() const { return m_shadowMapSizeAsPowerOf2; }
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

	virtual ShadowCameraTransform CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot);

	virtual void AddToEngine(CoreEngine* engine);
	inline Shader* GetShader() const { return m_shader; }
	inline ShadowInfo* GetShadowInfo() const { return m_shadowInfo;  }

protected:

	void SetShader(Shader* shader);
	void SetShadowInfo(ShadowInfo* shadowInfo);

};

struct DirectionalLight : public BaseLight
{
	float halfShadowArea;

	DirectionalLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0, int shadowMapSizeAsPowerOf2 = 0, float shadowArea = 80.0f, float shadowSoftness = 1.0f, float lightBleedReduction = 0.2f, float minVariance = 0.00002f);

	virtual ShadowCameraTransform CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot);
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

	SpotLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float viewAngle = ToRadians(170.0f), int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReduction = 0.2f, float minVariance = 0.00002f);
};

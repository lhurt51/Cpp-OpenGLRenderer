#pragma once

#include "../Shader/Shader.h"
#include "../../Core/Utils/Math/MathUtils.h"
#include "../../Core/ECS/GameComponent.h"

class CoreEngine;

class ShadowCameraTransform
{

	Vector3f	m_pos;
	Quaternion	m_rot;

public:

	ShadowCameraTransform(const Vector3f& pos, const Quaternion& rot) : m_pos(pos), m_rot(rot)
	{}

	inline const Vector3f& GetPos() const { return m_pos; }
	inline const Quaternion& GetRot() const { return m_rot; }

};

class ShadowInfo
{

	Matrix4f	m_projection;
	bool		m_flipFaces;
	int			m_shadowMapSizeAsPowerOf2;
	float		m_shadowSoftness;
	float		m_lightBleedReduction;
	float		m_varianceMin;

public:

	ShadowInfo(const Matrix4f& projection = Matrix4f().InitIdentity(), bool flipFaces = false, int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReduction = 0.2f, float minVariance = 0.00002f) :
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

	Shader		m_shader;
	ShadowInfo	m_shadowInfo;
	Vector3f	m_color;
	float		m_intensity;

public:

	BaseLight(const Vector3f& color, float intensity, const Shader& shader) : m_shader(shader), m_shadowInfo(ShadowInfo()), m_color(color), m_intensity(intensity)
	{}

	virtual ShadowCameraTransform CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot) const;

	virtual void AddToEngine(CoreEngine* engine) const;

	inline const Vector3f& GetColor() const { return m_color; }
	inline const float GetIntensity() const { return m_intensity; }
	inline const Shader& GetShader() const { return m_shader; }
	inline const ShadowInfo& GetShadowInfo() const { return m_shadowInfo;  }

protected:

	inline void SetShadowInfo(const ShadowInfo& shadowInfo) { m_shadowInfo = shadowInfo; }

};

class DirectionalLight : public BaseLight
{
	float m_halfShadowArea;

public:

	DirectionalLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0, int shadowMapSizeAsPowerOf2 = 0, float shadowArea = 80.0f, float shadowSoftness = 1.0f, float lightBleedReduction = 0.2f, float minVariance = 0.00002f);

	virtual ShadowCameraTransform CalcShadowCameraTransform(const Vector3f& mainCameraPos, const Quaternion& mainCameraRot) const;

	inline float GetHalfShadowArea() const { return m_halfShadowArea; }
};

class Attenuation
{
	float m_constant;
	float m_linear;
	float m_exponent;

public:

	Attenuation(float constant = 0, float linear = 0, float exponent = 1.0f) : m_constant(constant), m_linear(linear), m_exponent(exponent)
	{}

	inline float GetConstant() const { return m_constant; }
	inline float GetLinear() const { return m_linear; }
	inline float GetExponent() const { return m_exponent; }

};

class PointLight : public BaseLight
{
	Attenuation	m_atten;
	float		m_range;

public:

	PointLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), const Shader& shader = Shader("forward-point"));

	inline const Attenuation& GetAttenuation() const { return m_atten; }
	inline const float GetRange() const { return m_range; }

};

class SpotLight : public PointLight
{

	float m_cutoff;

public:

	SpotLight(const Vector3f& color = Vector3f(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float viewAngle = ToRadians(170.0f), int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReduction = 0.2f, float minVariance = 0.00002f);

	inline float GetCutoff() const { return m_cutoff; }

};

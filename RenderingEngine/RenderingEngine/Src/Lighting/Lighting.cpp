#include "Lighting.h"
#include "../RenderingEngine.h"
#include "../Shader.h"
#include "../CoreEngine.h"
#include <iostream>

#define COLOR_DEPTH 256

BaseLight::~BaseLight()
{
	if (m_shader) delete m_shader;
	if (m_shadowInfo) delete m_shadowInfo;
}

void BaseLight::AddToEngine(CoreEngine * engine)
{
	engine->GetRenderingEngine()->AddLight(this);
}

void BaseLight::SetShader(Shader * shader)
{
	if (m_shader) delete m_shader;
	m_shader = shader;
}

void BaseLight::SetShadowInfo(ShadowInfo* shadowInfo)
{
	if (m_shadowInfo) delete m_shadowInfo;
	m_shadowInfo = shadowInfo;
}

DirectionalLight::DirectionalLight(const Vector3f& color, float intensity) : BaseLight(color, intensity)
{
	SetShader(new Shader("forward-directional"));
	SetShadowInfo(new ShadowInfo(Matrix4f().InitOrthographic(-40, 40, -40, 40, -40, 40), true));
}

PointLight::PointLight(const Vector3f& color, float intensity, const Attenuation & atten) : BaseLight(color, intensity), atten(atten)
{
	float a = atten.exponent;
	float b = atten.linear;
	float c = atten.constant - COLOR_DEPTH * intensity * color.Max();

	range = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);

	SetShader(new Shader("forward-point"));
}

SpotLight::SpotLight(const Vector3f& color, float intensity, const Attenuation& atten, float viewAngle, int shadowMapSizeAsPowerOf2, float shadowSoftness, float lightBleedReduction, float minVariance) : PointLight(color, intensity, atten), cutoff(cos(viewAngle/2))
{
	SetShader(new Shader("forward-spot"));

	if (shadowMapSizeAsPowerOf2 != 0)
	{
		SetShadowInfo(new ShadowInfo(Matrix4f().InitPerspective(viewAngle, 1.0, 0.1, this->range), false, shadowSoftness, lightBleedReduction, minVariance));
	}
}
